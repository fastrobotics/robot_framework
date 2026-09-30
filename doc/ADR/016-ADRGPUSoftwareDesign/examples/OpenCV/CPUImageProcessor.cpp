#include "IImageProcessor.hpp"

class CPUImageProcessor : public IImageProcessor {
   public:
    void processFrame(const cv::Mat& input, cv::Mat& output) override {
        cv::Mat blurred;
        // Native CPU multi-threaded implementations
        cv::GaussianBlur(input, blurred, cv::Size(5, 5), 1.5);
        cv::Canny(blurred, output, 50.0, 150.0);
    }
};
IImageProcessor* createCPUImageProcessor() {
    // .release() unlinks the object from the unique_ptr manager
    // and returns a raw C-style pointer safely.
    return std::make_unique<CPUImageProcessor>().release();
}