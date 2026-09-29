#pragma once
#include <vector>

class IVectorProcessor {
   public:
    virtual ~IVectorProcessor() = default;

    // The shared interface contract that both execution engines must fulfill
    virtual void process(std::vector<float>& a, std::vector<float>& b, std::vector<float>& c) = 0;
};
