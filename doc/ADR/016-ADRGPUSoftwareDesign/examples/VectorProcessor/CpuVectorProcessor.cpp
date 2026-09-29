#include "CpuVectorProcessor.hpp"

CpuVectorProcessor::CpuVectorProcessor(size_t size) : dataSize(size) {}

void CpuVectorProcessor::process(std::vector<float>& a, std::vector<float>& b, std::vector<float>& c) {
// OpenMP splits the execution loop evenly over all active host CPU cores
#pragma omp parallel for
    for (size_t i = 0; i < dataSize; ++i) {
        c[i] = (a[i] * 2.0f) + (b[i] * 3.0f);
    }
}
