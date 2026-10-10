# Noise Reducer CPU/GPU Backend Implementation Plan

This is a proposed plan only. No GPU implementation or build changes have been made.

## Goal

Allow the depth-camera pipeline caller to select a CPU or GPU noise-reduction
backend at runtime, while retaining a working CPU-only build and preserving the
observable behavior of the existing reducer.

Follow the replaceable CPU/GPU implementation and caller-selected execution
model in [ADR 016](./016-ADRGPUSoftwareDesign.md), using the interface/backend
examples in [MathTest](./examples/MathTest/) and [OpenCVTest](./examples/OpenCVTest/).

## Current Baseline

- `NoiseReducer` currently combines the processing stages in the SensorFuser
  process. Its CPU implementation uses PCL for NaN removal and voxelization,
  then an OpenMP-parallel PCL KdTree query for radius-neighbor rejection.
- The benchmark uses 307,200 points (640x480), checks that isolated synthetic
  outliers are rejected, and enforces a 500ms average ceiling. The ideal target
  is 100ms.
- A recent run measured about 57ms average on this host. This is a CPU baseline,
  not a GPU performance guarantee.
- The top-level CMake currently enables CUDA for Jetson Orin Nano builds. Other
  architectures build without CUDA, so CPU support must remain independent of
  CUDA headers, targets, and runtime availability.

## Proposed Work

### 1. Specify the backend contract

- Document input/output behavior: preserve timestamp and RGB values, discard
  invalid XYZ samples, apply voxel downsampling and radius-neighbor rejection,
  and define the output cloud's organization/density metadata.
- Keep radius, neighbor-count, and voxel-size parameters identical across
  backends initially; don't tune GPU-only parameters as part of the port.
- Define how empty clouds, null cloud pointers, invalid parameters, and backend
  errors are reported.
- Clarify the selection policy: explicit CPU, explicit GPU, and automatic
  selection. Explicit GPU requests on CPU-only builds should return/report an
  unavailable-backend error. Automatic selection should choose CPU when CUDA is
  unavailable. Runtime execution errors must be visible; any CPU retry must be
  logged and covered by tests.

### 2. Separate the interface and CPU implementation

- Introduce a small noise-reducer backend interface, following the ADR examples.
  Keep PCL types at the API boundary initially to limit scope.
- Move the current CPU pipeline into a CPU backend without changing its
  behavior or the full-frame CPU benchmark.
- Add a backend factory/selector owned by the SensorFuser process. Use
  `std::unique_ptr` or another RAII-managed lifetime rather than the examples'
  raw-pointer factory pattern.
- Keep the CPU backend built and tested on every supported architecture.

### 3. Run a GPU feasibility spike on supported hardware

- Target the existing Jetson Orin Nano CUDA configuration first.
- Compare two implementation paths: available PCL GPU primitives versus custom
  CUDA kernels and a spatial index tailored to voxelized radius-neighbor
  counting.
- Prototype the full pipeline on-device: invalid-point compaction,
  voxelization/centroid and RGB reduction, spatial-neighbor construction, and
  radius/minimum-neighbor classification.
- Avoid transferring the cloud between host and device at each stage. Include
  allocation/setup and the final device-to-host transfer required by the
  current host-resident `PointCloudMsg` in measurements.
- Stop and retain CPU-only support if a correct end-to-end GPU path cannot
  outperform the CPU baseline or cannot be maintained on the supported CUDA
  toolchain.

### 4. Implement the optional GPU backend

- Add CUDA source and target conditionally, using the repository's architecture
  and CMake conventions. CPU-only configuration must not need CUDA installed.
- Keep device buffers/resources under RAII ownership and reuse capacity across
  frames where safe; handle resizing explicitly.
- Check and report CUDA allocation, launch, synchronization, and transfer
  failures. Do not silently return a success-shaped empty or unfiltered cloud.
- Synchronize only where required for output correctness and timing.

### 5. Verify correctness on both backends

- Run the same fixtures through both implementations: organized 640x480 input,
  NaNs, isolated outliers, empty/all-invalid clouds, and boundary cases at the
  configured radius and neighbor threshold.
- Check timestamps, RGB preservation, finite output, metadata, and retained /
  rejected point behavior. Compare centroids and floating-point coordinates
  within documented tolerances; compare outlier decisions exactly except for
  explicitly documented numerical boundary tolerance.
- Test forced CPU, forced GPU, automatic selection, CUDA-unavailable behavior,
  and surfaced runtime failures.
- Continue to run tests on a CPU-only build; run GPU tests only on CUDA-capable
  hardware.

### 6. Benchmark and decide whether to enable GPU selection

- Keep the 307,200-point benchmark input size and nonzero synthetic-outlier
  assertions.
- Compare CPU and GPU using identical input, parameters, warm-up, and measured
  iterations. Report average, median, high-percentile and maximum latency, plus
  input, post-voxel, and final point counts.
- Measure complete user-visible latency, including required host/device
  transfers; separately report stage timings for diagnosis.
- Require each backend to meet the 500ms average ceiling. Treat 100ms as the
  ideal average. Since the current CPU baseline is already below 100ms, enable
  automatic GPU selection only when full-pipeline GPU measurements demonstrate
  a repeatable end-to-end improvement on the target hardware.

## Completion Criteria

- CPU-only builds compile and pass tests without CUDA.
- The caller can explicitly select CPU/GPU or request automatic selection, with
  unavailable hardware and runtime errors reported clearly.
- CPU and GPU pass the shared semantic tests and the 307,200-point benchmark.
- GPU selection is enabled only for configurations where measured,
  transfer-inclusive performance justifies it; otherwise the CPU remains the
  default.
