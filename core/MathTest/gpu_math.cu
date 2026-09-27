#include <cuda_runtime.h>

#include <iostream>

#include "math_interface.h"

__global__ void vectorAddKernel(const float* a, const float* b, float* c, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        c[i] = a[i] + b[i];
    }
}

class GpuMath : public IVectorMath {
   public:
    void vectorAdd(const float* a, const float* b, float* c, int n) override {
        size_t size = n * sizeof(float);
        float *d_a = nullptr, *d_b = nullptr, *d_c = nullptr;

        // Allocate Device memory
        cudaMalloc(&d_a, size);
        cudaMalloc(&d_b, size);
        cudaMalloc(&d_c, size);

        // Copy input data to Device
        cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
        cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

        // Launch Kernel
        int threadsPerBlock = 256;
        int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;
        vectorAddKernel<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, n);

        // Bring results back to Host
        cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

        // Clean up internal GPU memory
        cudaFree(d_a);
        cudaFree(d_b);
        cudaFree(d_c);
    }
};

// Factory function to instantiate the GPU version
IVectorMath* createGpuMath() { return new GpuMath(); }
