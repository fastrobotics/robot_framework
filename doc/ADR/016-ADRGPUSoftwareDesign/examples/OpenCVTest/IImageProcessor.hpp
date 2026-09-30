#include <memory>
#include <opencv2/opencv.hpp>

class IImageProcessor {
   public:
    virtual ~IImageProcessor() = default;
    virtual void processFrame(const cv::Mat& input, cv::Mat& output) = 0;
};