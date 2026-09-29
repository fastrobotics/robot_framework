#include <cuda_runtime.h>

#include "math_interface.h"

// High-speed element-wise vector addition kernel
__global__ void vectorAddKernel(const float* a, const float* b, float* c, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        float x = a[i];
        float y = b[i];

        // Exact same logic, but executed by thousands of CUDA cores simultaneously
        for (int j = 0; j < 30; ++j) {
            x = (x + y) * 0.5f;
            y = (x - y) * 0.5f;
        }

        c[i] = x + y + 3.0f;
    }
}

class GpuMath : public IVectorMath {
   private:
    float* d_a = nullptr;
    float* d_b = nullptr;
    float* d_c = nullptr;

   public:
    void allocate(int n) override {
        size_t size = n * sizeof(float);
        cudaMalloc(&d_a, size);
        cudaMalloc(&d_b, size);
        cudaMalloc(&d_c, size);
    }

    void vectorAdd(const float* a, const float* b, float* c, int n) override {
        size_t size = n * sizeof(float);

        // Transfer data to internal pre-allocated VRAM buffers
        cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
        cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

        // Optimal execution grid mapping for hardware schedulers
        int threadsPerBlock = 256;
        int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

        vectorAddKernel<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, n);

        // Wait for execution pipe to clear before bringing back results
        cudaDeviceSynchronize();

        // Pull processed array structure back to application space
        cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    }

    void free() override {
        cudaFree(d_a);
        cudaFree(d_b);
        cudaFree(d_c);
        d_a = d_b = d_c = nullptr;
    }
};

IVectorMath* createGpuMath() { return new GpuMath(); }
