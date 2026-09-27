#pragma once

class IVectorMath {
   public:
    virtual ~IVectorMath() = default;

    // Pure virtual method to perform vector addition
    virtual void vectorAdd(const float* a, const float* b, float* c, int n) = 0;
};
