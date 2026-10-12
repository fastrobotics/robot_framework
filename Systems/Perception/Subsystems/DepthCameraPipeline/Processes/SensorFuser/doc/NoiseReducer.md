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
| `bool init()` | Initializes the reducer. Currently returns `true` without additional setup. |
| `PointCloudMsg reduceNoise(const PointCloudMsg& cloud)` | Returns the reduced cloud while preserving the input timestamp. |

The message contains a PCL `PointCloud<pcl::PointXYZRGB>` in its `point_cloud`
field. RGB values are carried through the PCL filtering operations along with
the point coordinates.

## How It Works

For a non-empty input cloud, `reduceNoise` applies these stages in order:

1. **Remove invalid coordinates.** PCL removes points with NaN values. The
   resulting cloud is marked dense.
2. **Voxel-grid downsampling.** PCL groups points into 3.5 cm cubic voxels and
   produces a representative point for each occupied voxel.
3. **Radius outlier filtering.** A spatial k-d tree searches each downsampled
   point for neighbors within 5 cm. A point is kept only when at least two
   *other* neighbors are found within that radius. The searches run in parallel
   when OpenMP is enabled; see [Parallel Processing](#parallel-processing).

The resulting cloud and original timestamp are returned in a `PointCloudMsg`.
Debug logs report the filtering point counts and timing for the NaN removal,
voxel, radius-filter, and complete stages.

## Parallel Processing

Parallelism is applied to the radius-outlier stage, after NaN removal and voxel
downsampling have completed. The k-d tree is built once from the downsampled
cloud. An OpenMP parallel region then distributes point indices across workers
using a static schedule, so each worker processes a contiguous share of the
index range.

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

The `#pragma omp` directives enable the parallel region when the build enables
OpenMP; otherwise execution may be serial. The number of workers is controlled
by the OpenMP runtime/build configuration, not by `NoiseReducer`.

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
  timestamp and an empty PCL cloud.
- An empty input cloud is returned unchanged.
- If NaN removal or voxel downsampling produces an empty result, the original
  input message is returned unchanged.
- If the radius-filter stage throws a standard exception, the exception is
  logged and the original cloud is used as the output cloud.
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
preservation, compare the parallel radius filter with PCL's reference filter,
and benchmark processing of a 640 × 480 cloud containing synthetic NaNs and
isolated depth spikes.