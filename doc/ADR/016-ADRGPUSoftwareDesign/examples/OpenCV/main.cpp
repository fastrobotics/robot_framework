#include <iostream>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/opencv.hpp>

int main() {
    std::cout << "========================================\n";
    std::cout << "Starting Jetson GPU OpenCV Processing...\n";
    std::cout << "========================================\n";

    // 1. Check for GPU
    if (cv::cuda::getCudaEnabledDeviceCount() == 0) {
        std::cerr << "Error: No CUDA-enabled devices found!\n";
        return -1;
    }
    cv::cuda::setDevice(0);

    // 2. Create a test image on the CPU (A 1080p canvas with patterns)
    std::cout << "[CPU] Generating a 1080p test pattern image...\n";
    cv::Mat h_input = cv::Mat::zeros(1080, 1920, CV_8UC1);

    // Draw some sharp shapes so Canny has edges to find
    cv::circle(h_input, cv::Point(960, 540), 300, cv::Scalar(255), -1);
    cv::rectangle(h_input, cv::Rect(400, 200, 300, 300), cv::Scalar(180), 10);
    cv::line(h_input, cv::Point(0, 0), cv::Point(1920, 1080), cv::Scalar(255), 5);

    // 3. Allocate GPU Mats
    cv::cuda::GpuMat d_input, d_blurred, d_edges;

    // 4. Upload CPU image to GPU Memory
    std::cout << "[GPU] Uploading image to VRAM...\n";
    d_input.upload(h_input);

    // 5. Create GPU Filter Objects (Reused across frames for efficiency)
    // Applying a 5x5 Gaussian blur to smooth out noise before edge detection
    cv::Ptr<cv::cuda::Filter> gaussian_filter =
        cv::cuda::createGaussianBlurFilter(CV_8UC1, CV_8UC1, cv::Size(5, 5), 1.5);

    // Create a GPU Canny Edge Detector
    cv::Ptr<cv::cuda::CannyEdgeDetector> canny_detector = cv::cuda::createCannyEdgeDetector(50.0, 150.0);

    // 6. Execute processing on the GPU
    std::cout << "[GPU] Running Gaussian Blur on CUDA cores...\n";
    gaussian_filter->apply(d_input, d_blurred);

    std::cout << "[GPU] Running Canny Edge Detection on CUDA cores...\n";
    canny_detector->detect(d_blurred, d_edges);

    // 7. Download result from GPU back to Host CPU memory
    std::cout << "[CPU] Downloading processed frames from VRAM...\n";
    cv::Mat h_output;
    d_edges.download(h_output);

    // 8. Save the final processed image to disk
    std::string filename = "gpu_edges_output.png";
    cv::imwrite(filename, h_output);
    std::cout << "SUCCESS: Processed image saved as '" << filename << "'\n";
    std::cout << "========================================\n";

    return 0;
}
