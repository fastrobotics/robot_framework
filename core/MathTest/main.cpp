#include <chrono>
#include <iostream>
#include <vector>

#include "math_interface.h"

// Declare the factory functions provided by our libraries
extern IVectorMath* createCpuMath();
#ifdef ARCHITECTURE_JETSONNANO
extern IVectorMath* createGpuMath();
#endif

void runTest(IVectorMath* engine, const std::string& name, int N) {
    std::vector<float> h_a(N, 1.0f);
    std::vector<float> h_b(N, 2.0f);
    std::vector<float> h_c(N, 0.0f);

    // Benchmark the implementation
    auto start = std::chrono::high_resolution_clock::now();

    engine->vectorAdd(h_a.data(), h_b.data(), h_c.data(), N);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    // Verify a random sample to confirm correctness
    bool correct = (h_c[N / 2] == 3.0f);

    std::cout << "[" << name << "] Time taken: " << duration.count()
              << " ms | Status: " << (correct ? "SUCCESS" : "FAILED") << std::endl;

    delete engine;
}

int main() {
    // 10 Million elements to notice a measurable timing difference
    const int N = 10'000'000;
    std::cout << "Running vector addition with " << N << " elements...\n" << std::endl;

    // Run the CPU implementation
    runTest(createCpuMath(), "CPU Math Library", N);
#ifdef ARCHITECTURE_JETSONNANO
    // Run the GPU implementation
    runTest(createGpuMath(), "GPU Math Library", N);
#endif

    return 0;
}
