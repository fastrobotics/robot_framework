#include "math_interface.h"

class CpuMath : public IVectorMath {
   public:
    void vectorAdd(const float* a, const float* b, float* c, int n) override {
        for (int i = 0; i < n; ++i) {
            c[i] = a[i] + b[i];
        }
    }
};

// Factory function to instantiate the CPU version
IVectorMath* createCpuMath() { return new CpuMath(); }
