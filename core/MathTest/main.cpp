#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "math_interface.h"

extern IVectorMath* createCpuMath();
#ifdef ARCHITECTURE_JETSONNANO
extern IVectorMath* createGpuMath();
#endif

void runBenchmark(IVectorMath* engine, const std::string& name, int N, int iterations) {
    std::vector<float> h_a(N, 1.0f);
    std::vector<float> h_b(N, 2.0f);
    std::vector<float> h_c(N, 0.0f);

    std::cout << "--- Benchmarking: " << name << " ---" << std::endl;

    // Upfront hardware resource configuration
    engine->allocate(N);

    // Warm-up iteration to stabilize driver pipelines and system caches
    engine->vectorAdd(h_a.data(), h_b.data(), h_c.data(), N);

    double totalDurationMs = 0.0;

    for (int i = 0; i < iterations; ++i) {
        std::fill(h_c.begin(), h_c.end(), 0.0f);

        auto start = std::chrono::high_resolution_clock::now();

        engine->vectorAdd(h_a.data(), h_b.data(), h_c.data(), N);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        totalDurationMs += duration.count();
    }

    // Clean up pipeline infrastructure
    engine->free();

    double averageDurationMs = totalDurationMs / iterations;
    bool correct = (h_c[N / 2] == 3.0f);

    std::cout << "Average Execution Time over " << iterations << " iterations: " << averageDurationMs << " ms"
              << std::endl;
    std::cout << "Validation Check: " << (correct ? "PASSED" : "FAILED") << "\n" << std::endl;

    delete engine;
}

int main() {
    const int N = 10'000'000'000;
    const int ITERATIONS = 10;

    std::cout << "Initializing Benchmark Framework..." << std::endl;
    std::cout << "Vector Size: " << N << " elements (~40 MB per vector)\n" << std::endl;

    // runBenchmark(createCpuMath(), "CPU Math Engine", N, ITERATIONS);

#ifdef ARCHITECTURE_JETSONNANO
    runBenchmark(createGpuMath(), "GPU Math Engine (NVIDIA CUDA)", N, ITERATIONS);
#else
    std::cout << "[INFO] GPU Engine disabled via compile flags. Skipping GPU test." << std::endl;
#endif

    return 0;
}
