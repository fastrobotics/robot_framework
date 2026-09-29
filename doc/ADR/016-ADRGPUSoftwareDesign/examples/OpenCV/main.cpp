#include
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/opencv.hpp>
int main() {
    std::cout << "Starting Jetson GPU OpenCV Processing..." << std::endl;
    if (cv::cuda::getCudaEnabledDeviceCount() == 0) {
        std::cerr << "Error: No CUDA devices found!" << std::endl;
        return -1;
    }
    cv::cuda::setDevice(0);
    std::cout << "[CPU] Generating a 1080p test pattern image..." << std::endl;
    cv::Mat h_input = cv::Mat::zeros(1080, 1920, CV_8UC1);
    cv::circle(h_input, cv::Point(960, 540), 300, cv::Scalar(255), -1);
    cv::rectangle(h_input, cv::Rect(400, 200, 300, 300), cv::Scalar(180), 10);
    cv::line(h_input, cv::Point(0, 0), cv::Point(1920, 1080), cv::Scalar(255), 5);
    cv::cuda::GpuMat d_input, d_blurred, d_edges;
    std::cout << "[GPU] Uploading image to VRAM..." << std::endl;
    d_input.upload(h_input);
    cv::Ptrcv::cuda::Filter gaussian_filter = cv::cuda::createGaussianFilter(CV_8UC1, CV_8UC1, cv::Size(5, 5), 1.5);
    cv::Ptrcv::cuda::CannyEdgeDetector canny_detector = cv::cuda::createCannyEdgeDetector(50.0, 150.0);
    std::cout << "[GPU] Running Gaussian Blur on CUDA cores..." << std::endl;
    gaussian_filter->apply(d_input, d_blurred);
    std::cout << "[GPU] Running Canny Edge Detection on CUDA cores..." << std::endl;
    canny_detector->detect(d_blurred, d_edges);
    std::cout << "[CPU] Downloading processed frames from VRAM..." << std::endl;
    cv::Mat h_output;
    d_edges.download(h_output);
    std::string filename = "gpu_edges_output.png";
    cv::imwrite(filename, h_output);
    std::cout << "SUCCESS: Processed image saved as " << filename << std::endl;
    return 0;
}
