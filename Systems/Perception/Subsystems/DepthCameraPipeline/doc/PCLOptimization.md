# Context Summary: PCL Noise Filter Optimization Tracking
>> Address during AB5765
## 📌 Current Status & Target Function
* **Target File:** `/home/david/git/robot_framework/Systems/Perception/Subsystems/DepthCameraPipeline/Processes/SensorFuser/src/NoiseReducer.cpp`
* **Target Function:** `fast::rf::PerceptionSystem::DepthCameraPipelineSubsystem::SensorFuser::NoiseReducer::reduceNoise(...)`
* **Performance Gain:** Improved from an unusable **1.6 seconds (0.6 Hz)** per frame down to **150ms (~6.5 Hz)**.
* **Goal:** Reach real-time speed (under 30-50ms total frame budget) on a laptop CPU without losing RGB point metrics.

---

## 🛠️ Completed Implementations & Fixes

1. **RGB Color Loss Resolution:**
   * Ensured the filter pipeline explicitly templates across `<pcl::PointXYZRGB>` throughout the entire stack, successfully keeping valid color fields.

2. **Stability Fixes (Crash Prevention):**
   * Pre-allocated heap instances using `new pcl::PointCloud<pcl::PointXYZRGB>` before running conversions to avoid null pointer dereferences.
   * Added `pcl::removeNaNFromPointCloud` to prevent spatial `KdTree` abort crashes (`exit code -6 / SIGABRT`) caused by invalid camera depth points.
   * Wrapped the execution blocks inside standard `try {} catch(...)` patterns to insulate the node against internal library faults.

3. **Memory Optimization:**
   * Shifted the main processing entry point signature to pass variables by constant reference (`const &`) to stop expensive heap-copy-by-value behaviors on incoming sensor messages.

4. **Algorithmic Tuning (The 1500ms ➡️ 110ms Drop):**
   * Added an upfront `pcl::VoxelGrid` step to drastically shrink core calculations.
   * **Crucial Fix:** Removed the manual `ror.setSearchMethod(tree);` override. Passing an explicit `pcl::search::KdTree` was forcing a costly \(O(N^2)\) structural rebuild every query step. Removing it allowed PCL to fall back to its internal, optimized caching mechanisms.

---

## 📊 Latest Performance Profiles (Telemetry Logs)
```log
InConv: 3ms | NaN_Rem: 3ms | Voxel: 22ms | RadFilter: 106ms | OutConv: 0ms || Total: 153ms
```
* **Analysis:** Conversions and downsampling are highly optimized. The bottleneck is entirely trapped inside the spatial distance evaluations of `RadFilter` (106ms-117ms), which currently pins exactly one CPU core at 100% while leaving remaining threads idle.

---

## 🚀 Future Roadmap & Next Steps for VS Code Copilot

When resuming this optimization task, prompt Copilot to address these three areas:

1. **Next Planned Optimization Step (Geometric Bypass):**
   * Adjust the structural parameters to tie the voxel bounds directly to a tight radius search circle. 
   * *Proposed Mapping:* Set `VoxelSize` to `0.030f` (3cm), set `RadiusSearch` to `0.035` (3.5cm), and adjust `MinNeighbors` down to `1`. This forces the internal K-d tree to only analyze immediate spatial cells, reducing distance checking overhead down to a projected <30ms window.

2. **Unlock Hardware Vectorization (SIMD / Auto-Parallelization):**
   * Investigate why compilation flags aren't engaging AVX2/SSE extensions. Copilot should review the package's top-level `CMakeLists.txt` configuration files to verify that options like `-march=native` and `-O3` are actively being applied to the build target.

3. **Move to Isolated Unit Benchmarking:**
   * Shift away from tedious manual bag/log playback routines. Leverage the existing unit test suite framework found in `/src/test/test_depthCameraSensorNoiseReducer.cpp` by writing a dedicated Google Test harness (`gtest`) that injects a synthetic or mocked point cloud array to rapidly measure profile times in milliseconds.
