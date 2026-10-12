`@compare_tag Process-Document v0.1`

[SensorFuser Process](Process-SensorFuser.md)

- [NoiseReducer](#noisereducer)
  - [Purpose](#purpose)
  - [Interface](#interface)
  - [How It Works](#how-it-works)
  - [Parallel Processing](#parallel-processing)
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
| `bool init()` | Selects and initializes the GPU backend when CUDA is built and a usable device is present; otherwise initializes the CPU backend. |
| `bool setConfig(double voxelSize_m, double radius_m, uint64_t minNeighborCount)` | Sets finite, positive sizes and the minimum count used by both backends. |
| `PointCloudMsg reduceNoise(const PointCloudMsg& cloud)` | Returns the reduced cloud while preserving the input timestamp. |

The message contains a PCL `PointCloud<pcl::PointXYZRGB>` in its `point_cloud`
field. RGB values are carried through the PCL filtering operations along with
the point coordinates.

The public `NoiseReducer` delegates to an `INoiseReducer` implementation:
`CPUNoiseReducer` or `GPUNoiseReducer`. The automatic selector checks CUDA
device availability at initialization. CPU-only builds and systems without a
usable CUDA device use the CPU implementation. If a selected GPU backend fails
during initialization or processing, the error is reported; processing errors
are rethrown and are not silently retried on CPU.

## How It Works

For a non-empty input cloud, `reduceNoise` applies these stages in order:

1. **Remove invalid coordinates.** PCL removes points with NaN values. The
   resulting cloud is marked dense.
2. **Voxel-grid downsampling.** PCL groups points into 3.5 cm cubic voxels and
   produces a representative point for each occupied voxel.
3. **Radius outlier filtering.** A spatial k-d tree searches each downsampled
   point for neighbors within 5 cm. A point is kept only when at least two
   *other* neighbors are found within that radius. The CPU backend runs these
   searches in parallel with OpenMP; the CUDA backend builds a uniform spatial
   cell index and classifies neighbors in parallel on the GPU.

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
controlled by the OpenMP runtime/build configuration, not by `NoiseReducer`.

## Filter Parameters

The defaults are set by `NoiseReducer` and can be overridden with
`setConfig(voxelSize_m, radius_m, minNeighborCount)`:

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

The `BasicSensorFuserProcess` passes the overlap-removed cloud to
`NoiseReducer::reduceNoise` and uses the returned message as the fused cloud.
See [Process: SensorFuser](Process-SensorFuser.md) for the surrounding
combination and overlap-removal flow.

## Validation

The reducer tests are in
`../src/test/test_depthCameraSensorNoiseReducer.cpp`. They check timestamp
preservation, compare reducer output with PCL's reference filter, validate
configuration and invalid/empty input behavior, and benchmark processing of a
640 × 480 cloud containing synthetic NaNs and isolated depth spikes. The
benchmark compares the explicit CPU backend with automatic selection and
reports average, median, 95th-percentile, and maximum latency. On a Jetson build
with a usable CUDA device, automatic selection measures the GPU backend and a
separate test compares GPU output with the CPU result.