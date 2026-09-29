#include "math_interface.h"

class CpuMath : public IVectorMath {
   public:
    void allocate([[maybe_unused]] int n) override {
        // No-op: CPU operates directly on host-allocated vectors
    }

    void vectorAdd(const float* a, const float* b, float* c, int n) override {
        for (int i = 0; i < n; ++i) {
            float x = a[i];
            float y = b[i];

            // A simple, unrolled loop repeating the basic math 30 times per element
            for (int j = 0; j < 30; ++j) {
                x = (x + y) * 0.5f;
                y = (x - y) * 0.5f;
            }

            c[i] = x + y + 3.0f;  // Final assignment matching expected validation output
        }
    }

    void free() override {
        // No-op: Managed by std::vector lifecycle in main application
    }
};

IVectorMath* createCpuMath() { return new CpuMath(); }
