#include <chrono>
#include <iostream>
#include <memory>

#include "CpuVectorProcessor.hpp"
#ifdef ARCHITECTURE_JETSONNANO
#include "GpuVectorProcessor.hpp"
#endif
#include "IVectorProcessor.hpp"

// Helper routing function accepting the generic common interface
void executeAndProfile(const std::string& label, IVectorProcessor& processor, std::vector<float>& a,
                       std::vector<float>& b, std::vector<float>& c) {
    std::cout << "\nExecuting: " << label << "..." << std::endl;
    std::fill(c.begin(), c.end(), 0.0f);  // Ensure target buffer is zeroed out

    auto start = std::chrono::high_resolution_clock::now();

    // Virtual interface resolution dispatching to the targeted implementation block
    processor.process(a, b, c);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "-> Finished in: " << elapsed.count() << " ms" << std::endl;
    std::cout << "-> Verification Element: " << c[0] << " (Expected: 10.5)" << std::endl;
}

int main() {
    const size_t N = 500'000'000;
    std::cout << "Allocating and preparing data buffers with " << N << " items..." << std::endl;

    std::vector<float> A(N, 1.5f);
    std::vector<float> B(N, 2.5f);
    std::vector<float> C(N, 0.0f);

    // Instantiate processing variants polymorphically via the interface base class
    std::unique_ptr<IVectorProcessor> cpuEngine = std::make_unique<CpuVectorProcessor>(N);
#ifdef ARCHITECTURE_JETSONNANO
    std::unique_ptr<IVectorProcessor> gpuEngine = std::make_unique<GpuVectorProcessor>(N);
#endif

    // Route both engines down the polymorphic benchmark tracking loop
    executeAndProfile("Multi-Core CPU Pipeline (OpenMP)", *cpuEngine, A, B, C);
#ifdef ARCHITECTURE_JETSONNANO
    executeAndProfile("Accelerated GPU Pipeline (NVIDIA stdpar)", *gpuEngine, A, B, C);
#endif

    return 0;
}
