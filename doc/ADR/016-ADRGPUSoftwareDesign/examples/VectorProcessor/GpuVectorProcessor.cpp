#include "GpuVectorProcessor.hpp"

#include <algorithm>
#include <execution>  // Required for std::execution parallel policies
#include <numeric>

GpuVectorProcessor::GpuVectorProcessor(size_t size) : dataSize(size) {}

void GpuVectorProcessor::process(std::vector<float>& a, std::vector<float>& b, std::vector<float>& c) {
    std::vector<size_t> indices(dataSize);
    std::iota(indices.begin(), indices.end(), 0);

    // Vectorized execution policy mapping directly to NVIDIA GPUs under the nvc++ compiler [1.1]
    std::for_each(std::execution::par_unseq, indices.begin(), indices.end(),
                  [&](size_t i) { c[i] = (a[i] * 2.0f) + (b[i] * 3.0f); });
}
