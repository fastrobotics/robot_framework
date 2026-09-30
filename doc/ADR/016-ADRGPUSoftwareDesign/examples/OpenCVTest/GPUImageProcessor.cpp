#include <iostream>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudaimgproc.hpp>

#include "IImageProcessor.hpp"

class GPUImageProcessor : public IImageProcessor {
   private:
    cv::cuda::GpuMat d_input, d_blurred, d_edges;
    cv::Ptr<cv::cuda::Filter> gaussian_filter;
    cv::Ptr<cv::cuda::CannyEdgeDetector> canny_detector;

   public:
    GPUImageProcessor() {
        // Initialize Jetson Orin Nano's onboard GPU
        cv::cuda::setDevice(0);

        // Pre-allocate filter configurations for max loop speed
        gaussian_filter = cv::cuda::createGaussianFilter(CV_8UC1, CV_8UC1, cv::Size(5, 5), 1.5);
        canny_detector = cv::cuda::createCannyEdgeDetector(50.0, 150.0);
    }

    void processFrame(const cv::Mat& input, cv::Mat& output) override {
        // 1. Send data to VRAM
        d_input.upload(input);

        // 2. Process on CUDA cores
        gaussian_filter->apply(d_input, d_blurred);
        canny_detector->detect(d_blurred, d_edges);

        // 3. Bring result back to CPU RAM
        d_edges.download(output);
    }
};

// Factory instantiation returning a clean raw pointer
extern "C" IImageProcessor* createGPUImageProcessor() { return new GPUImageProcessor(); }