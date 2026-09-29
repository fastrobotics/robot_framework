#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "IVectorMath.hpp"

extern IVectorMath* createCPUMath();
#ifdef ARCHITECTURE_JETSONNANO
extern IVectorMath* createGPUMath();
#endif

double runBenchmark(IVectorMath* engine, const std::string& name, int N, int iterations) {
    constexpr int PROGRESS_INTERVAL = 10'000'000;
    std::vector<float> h_a(N, 1.0f);
    std::vector<float> h_b(N, 2.0f);
    std::vector<float> h_c(N, 0.0f);

    std::cout << "--- Benchmarking: " << name << " ---" << std::endl;

    // Upfront hardware resource configuration
    engine->allocate(N);

    auto runWithProgress = [&](const std::string& stage) {
        double durationMs = 0.0;
        std::cout << stage << " started" << std::endl;

        for (int offset = 0; offset < N; offset += PROGRESS_INTERVAL) {
            int chunkSize = std::min(PROGRESS_INTERVAL, N - offset);
            auto start = std::chrono::high_resolution_clock::now();
            engine->vectorAdd(h_a.data() + offset, h_b.data() + offset, h_c.data() + offset, chunkSize);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> duration = end - start;
            durationMs += duration.count();
            int percentComplete = static_cast<int>(100LL * (offset + chunkSize) / N);
            std::cout << stage << ": " << percentComplete << "% complete" << std::endl;
        }

        return durationMs;
    };

    // Warm-up iteration to stabilize driver pipelines and system caches
    runWithProgress("Warm-up");

    double totalDurationMs = 0.0;

    for (int i = 0; i < iterations; ++i) {
        std::fill(h_c.begin(), h_c.end(), 0.0f);
        totalDurationMs += runWithProgress("Iteration " + std::to_string(i + 1) + "/" + std::to_string(iterations));
    }

    // Clean up pipeline infrastructure
    engine->free();

    double averageDurationMs = totalDurationMs / iterations;
    bool correct = std::abs(h_c[N / 2] - 3.0f) < 1e-5f;

    std::cout << "Average Execution Time over " << iterations << " iterations: " << averageDurationMs << " ms"
              << std::endl;
    std::cout << "Validation Check: " << (correct ? "PASSED" : "FAILED") << "\n" << std::endl;

    delete engine;
    return averageDurationMs;
}

int main() {
    constexpr int FIRST_VECTOR_SIZE = 1'000'000;
    constexpr int SWEEP_STEP = 10'000'000;
    constexpr int MAX_VECTOR_SIZE = 100'000'000;
    const int ITERATIONS = 5;
    std::vector<int> vectorSizes{FIRST_VECTOR_SIZE};
    for (int size = SWEEP_STEP; size <= MAX_VECTOR_SIZE; size += SWEEP_STEP) {
        vectorSizes.push_back(size);
    }

    std::cout << "Initializing Benchmark Framework..." << std::endl;

#ifdef ARCHITECTURE_JETSONNANO
    struct SweepResult {
        int vectorSize;
        double cpuDurationMs;
        double gpuDurationMs;
    };
    std::vector<SweepResult> results;

    for (int size : vectorSizes) {
        double memoryPerVectorMb = static_cast<double>(size) * sizeof(float) / 1'000'000.0;
        std::cout << "\n=== Vector Size: " << size << " elements (~" << memoryPerVectorMb
                  << " MB per vector) ===" << std::endl;

        double cpuAverageDurationMs = runBenchmark(createCPUMath(), "CPU Math Engine", size, ITERATIONS);
        double gpuAverageDurationMs = runBenchmark(createGPUMath(), "GPU Math Engine (NVIDIA CUDA)", size, ITERATIONS);
        results.push_back({size, cpuAverageDurationMs, gpuAverageDurationMs});

        std::cout << "Sweep summary for " << size << " elements: CPU " << cpuAverageDurationMs << " ms, GPU "
                  << gpuAverageDurationMs << " ms";
        if (gpuAverageDurationMs > 0.0) {
            std::cout << ", speedup " << cpuAverageDurationMs / gpuAverageDurationMs << "x";
        } else {
            std::cout << ", speedup unavailable (GPU duration was zero)";
        }
        std::cout << std::endl;
    }

    std::cout << "\n=== Final Sweep Summary ===" << std::endl;
    std::cout << "Vector Size | CPU (ms) | GPU (ms) | Speedup" << std::endl;
    for (const auto& result : results) {
        std::cout << result.vectorSize << " | " << result.cpuDurationMs << " | " << result.gpuDurationMs << " | ";
        if (result.gpuDurationMs > 0.0) {
            std::cout << result.cpuDurationMs / result.gpuDurationMs << "x";
        } else {
            std::cout << "unavailable";
        }
        std::cout << std::endl;
    }
#else
    for (int size : vectorSizes) {
        double memoryPerVectorMb = static_cast<double>(size) * sizeof(float) / 1'000'000.0;
        std::cout << "\n=== Vector Size: " << size << " elements (~" << memoryPerVectorMb
                  << " MB per vector) ===" << std::endl;
        double cpuAverageDurationMs = runBenchmark(createCPUMath(), "CPU Math Engine", size, ITERATIONS);
        std::cout << "Sweep summary for " << size << " elements: CPU " << cpuAverageDurationMs << " ms, GPU unavailable"
                  << std::endl;
    }
    std::cout << "[INFO] GPU Engine disabled via compile flags. Skipping GPU test." << std::endl;
#endif

    return 0;
}
