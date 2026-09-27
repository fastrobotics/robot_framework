#include "math_interface.h"

class CpuMath : public IVectorMath {
   public:
    void allocate(int n) override {
        // No-op: CPU operates directly on host-allocated vectors
    }

    void vectorAdd(const float* a, const float* b, float* c, int n) override {
        for (int i = 0; i < n; ++i) {
            c[i] = a[i] + b[i];
        }
    }

    void free() override {
        // No-op: Managed by std::vector lifecycle in main application
    }
};

IVectorMath* createCpuMath() { return new CpuMath(); }
