#include "IImageProcessor.hpp"

class CPUImageProcessor : public IImageProcessor {
   public:
    void processFrame(const cv::Mat& input, cv::Mat& output) override {
        cv::Mat blurred;
        cv::GaussianBlur(input, blurred, cv::Size(5, 5), 1.5);
        cv::Canny(blurred, output, 50.0, 150.0);
    }
};
IImageProcessor* createCPUImageProcessor() { return std::make_unique<CPUImageProcessor>().release(); }