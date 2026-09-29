#pragma once

class IVectorMath {
   public:
    virtual ~IVectorMath() = default;

    // Upfront memory initialization and allocation
    virtual void allocate(int n) = 0;

    // Pure processing execution loop
    virtual void vectorAdd(const float* a, const float* b, float* c, int n) = 0;

    // Memory teardown and resource optimization
    virtual void free() = 0;
};
