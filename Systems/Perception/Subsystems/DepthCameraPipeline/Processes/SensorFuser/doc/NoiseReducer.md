`@compare_tag Process-Document v0.1`

[SensorFuser Process](Process-SensorFuser.md)

- [NoiseReducer](#noisereducer)
  - [Purpose](#purpose)
  - [Interface](#interface)
  - [How It Works](#how-it-works)
  - [Parallel Processing](#parallel-processing)
  - [CPU Implementation](#cpu-implementation)
  - [GPU Implementation](#gpu-implementation)
  - [Filter Parameters](#filter-parameters)
  - [Input and Error Handling](#input-and-error-handling)
  - [Usage in SensorFuser](#usage-in-sensorfuser)
  - [Validation](#validation)

# NoiseReducer

## Purpose

`NoiseReducer` filters a fused RGB point cloud to reduce invalid measurements and
isolated points. It is used by the [SensorFuser process](Process-SensorFuser.md)
after the sensor clouds have been combined and overlapping regions removed.

The reducer removes NaN points, lowers point density with voxel-grid
downsampling, and rejects points that do not have enough nearby neighbors.

## Interface

| Method | Description |
| --- | --- |
| `bool setConfig(const NoiseReducerConfig& config)` | Sets finite, positive sizes and the minimum count used by both backends. |
| `bool init()` | Initializes the already selected backend. The GPU backend reports failure if CUDA cannot initialize; it does not fall back to CPU. |
| `PointCloudMsg reduceNoise(const PointCloudMsg& input)` | Returns the reduced cloud while preserving the input timestamp. |

The message contains a PCL `PointCloud<pcl::PointXYZRGB>` in its `point_cloud`
field. RGB values are carried through the PCL filtering operations along with
the point coordinates.

`INoiseReducer` is a pure interface. `BaseNoiseReducer` implements shared
configuration, input handling, and preprocessing. `CPUNoiseReducer` and
`GPUNoiseReducer` derive from the base and provide their radius-filter
implementation. `BasicSensorFuserProcess` owns a `std::unique_ptr<INoiseReducer>`
and instantiates the backend selected for the build.

### Backend build and selection

| Build target | Contents and dependencies | Process selection |
| --- | --- | --- |
| `baseNoiseReducer` | Common implementation; shared by either backend. | Linked transitively through the selected backend. |
| `noiseReducerCPU` | CPU radius filtering using PCL and OpenMP; depends on `baseNoiseReducer`. | Selected on non-Jetson builds. |
| `noiseReducerGPU` | CUDA radius filtering; depends on `baseNoiseReducer` and CUDA runtime, not on `noiseReducerCPU`. Built for Jetson Orin Nano. | Selected on Jetson Orin Nano builds. |

The CPU and GPU libraries are separate alternatives: neither backend library
depends on the other. The Jetson CUDA compilation enables
`--expt-relaxed-constexpr` for `noiseReducerGPU` to permit CUDA device code to
call the relevant host/device constexpr functions. GPU initialization fails
explicitly if no CUDA device is available. Processing errors are logged and
re-thrown, not silently retried on CPU.

## How It Works

For a non-empty input cloud, `reduceNoise` applies these stages in order:

1. **Remove invalid coordinates.** PCL removes points with NaN values. The
   resulting cloud is marked dense.
2. **Voxel-grid downsampling.** PCL groups points into 3.5 cm cubic voxels and
   produces a representative point for each occupied voxel.
3. **Radius outlier filtering.** Each backend searches for neighbors within
   5 cm of every downsampled point. A point is kept only when at least two
   *other* neighbors are found within that radius. The CPU backend uses a
   spatial k-d tree and runs searches in parallel with OpenMP; the CUDA backend
   builds a uniform spatial cell index and classifies neighbors in parallel on
   the GPU.

NaN removal and voxel downsampling currently remain PCL CPU stages for both
backends. In the CUDA backend, the downsampled positions are transferred to the
device once for radius classification and the inlier flags are transferred
back to assemble the output cloud. This boundary can be moved further onto the
GPU if end-to-end measurements justify implementing and validating GPU voxel
aggregation.

The resulting cloud and original timestamp are returned in a `PointCloudMsg`.

## Parallel Processing

For the CPU backend, parallelism is applied to the radius-outlier stage, after
NaN removal and voxel downsampling have completed. The k-d tree is built once
from the downsampled cloud. An OpenMP parallel region then distributes point
indices across workers using a static schedule, so each worker processes a
contiguous share of the index range.

Each worker reuses its own neighbor-index and distance buffers while querying
the tree. For each point, the search requests `minNeighborCount + 1` neighbors:
the point itself is included in the search result, so this requires the
configured number of *other* points. A point is marked as an inlier only if the
search returns that many points and the farthest returned neighbor is within
the configured radius.

Workers write only the inlier flag for the point index they are processing.
After the parallel region finishes, a serial pass gathers the inlier indices in
ascending input order, and PCL copies those points into the output. This keeps
the output ordering deterministic while parallelizing the independent neighbor
searches. NaN removal, voxel downsampling, and final result assembly are not
parallelized by this helper.

The CPU `#pragma omp` directives enable the parallel region when the build
enables OpenMP; otherwise execution may be serial. The number of workers is
controlled by the OpenMP runtime/build configuration, not by the reducer.
The GPU backend also parallelizes point classification, using CUDA kernels
after transferring the downsampled point positions to device memory.

## CPU Implementation

`CPUNoiseReducer` implements the radius stage with a PCL k-d tree. It builds
the tree once from the preprocessed cloud, then calls `nearestKSearch` for
each point, requesting `minNeighborCount + 1` results because the query point
itself is included. A point is retained when the requested number of results
is found and the farthest returned neighbor is no farther than the configured
radius. The OpenMP loop processes independent queries with a static schedule;
each worker has its own query buffers. A final serial gather preserves input
order.

This backend requires PCL and OpenMP. If OpenMP parallelism is not enabled by
the build/runtime, the same loop can execute serially.

## GPU Implementation

`GPUNoiseReducer` accelerates only the radius stage; NaN removal and voxel
downsampling still run on the CPU through `BaseNoiseReducer`. It selects CUDA
device 0 during initialization and fails initialization if CUDA cannot report
a device or no device is available. A selected GPU backend does not silently
fall back to CPU.

For radius filtering, the implementation copies the downsampled XYZ positions
to a compact host buffer and uploads them to the GPU. It then:

1. Uses a CUDA kernel to map every point to a uniform spatial cell whose edge
   length is the configured neighbor radius, producing a linear cell key and
   the point's original index.
2. Sorts cell keys and their associated point indices together with Thrust.
3. Launches a CUDA thread for each point. The thread visits its own cell and
   the surrounding 26 cells (fewer at grid boundaries), finds each cell's
   range in the sorted keys by binary search, and counts candidates whose
   squared Euclidean distance is within the squared radius. Since each cell is
   one radius wide, any point within radius must be in one of these 27 cells.
   Counting stops once `minNeighborCount + 1` points, including the query
   point, have been found.
4. Copies the inlier flags back to the host and gathers retained points in
   their original order. The gather uses the original PCL points, so RGB
   values and other point fields are preserved without transferring them to
   the device.

The CUDA implementation checks device selection, kernel launches, result
transfers, and grid/index ranges. Failures are surfaced as exceptions (and
logged by the shared reducer) rather than returning an unfiltered cloud.
Compared with the CPU backend, it trades spatial-index construction and
neighbor searches for device transfers, key sorting, and cell lookups; actual
performance therefore depends on cloud size and the target GPU.

## Filter Parameters

The defaults are set by `NoiseReducerConfig` and can be overridden through
`INoiseReducer::setConfig`:

| Parameter | Value | Effect |
| --- | --- | --- |
| Voxel leaf size | 0.035 m on each axis by default | Sets the spatial resolution for downsampling. |
| Neighbor radius | 0.05 m by default | Defines the radius used to search for nearby points. |
| Minimum neighbors | 2 by default | Requires this many other points within the radius for a point to survive. |

## Input and Error Handling

- A null `point_cloud` is logged as an error. The returned message has the input
  timestamp and an empty dense PCL cloud.
- An empty input cloud is returned unchanged.
- If NaN removal or voxel downsampling produces an empty result, an empty dense
  cloud is returned with the input timestamp.
- Invalid configurations are rejected by `setConfig`.
- Backend processing exceptions are logged and rethrown; a GPU failure does
  not trigger a CPU retry or return an unfiltered cloud.
- For ordinary successful filtering, the output cloud is the result of all
  three filtering stages.

## Usage in SensorFuser

The `BasicSensorFuserProcess` passes the overlap-removed cloud through its
`INoiseReducer` pointer and uses the returned message as the fused cloud. The
concrete implementation is chosen at build time: Jetson Orin Nano uses
`GPUNoiseReducer`, and other supported builds use `CPUNoiseReducer`. See
[Process: SensorFuser](Process-SensorFuser.md) for the surrounding
combination and overlap-removal flow.

## Validation

The reducer tests are in
`../src/NoiseReducer/test/test_depthCameraSensorNoiseReducer.cpp`. They check
timestamp preservation, compare CPU reducer output with PCL's reference
filter, validate configuration and invalid/empty input behavior, and benchmark
processing of a 640 × 480 cloud containing synthetic NaNs and isolated depth
spikes. The benchmark compares the explicit CPU backend with the
process-selected backend and reports average, median, 95th-percentile, and
maximum latency. On Jetson, the selected backend is GPU; a separate test
compares GPU output with the CPU result when a CUDA device is available.