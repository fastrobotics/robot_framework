#pragma once
#include "IVectorProcessor.hpp"

class GpuVectorProcessor : public IVectorProcessor {
   private:
    size_t dataSize;

   public:
    explicit GpuVectorProcessor(size_t size);
    void process(std::vector<float>& a, std::vector<float>& b, std::vector<float>& c) override;
};
