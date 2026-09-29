#include <iostream>
#include <opencv2/core/cuda.hpp>
#include <opencv2/opencv.hpp>

int main() {
    // 1. Query the Jetson for CUDA-capable hardware through OpenCV
    int cuda_devices = cv::cuda::getCudaEnabledDeviceCount();
    std::cout << "========================================" << std::endl;
    std::cout << "CUDA-enabled Devices Found: " << cuda_devices << std::endl;

    if (cuda_devices > 0) {
        // 2. Target the Orin Nano's onboard Ampere GPU
        cv::cuda::setDevice(0);

        // 3. Create a standard CPU matrix (1080p resolution)
        cv::Mat h_mat = cv::Mat::ones(1080, 1920, CV_8UC3) * 128;

        // 4. Create a GPU Matrix
        cv::cuda::GpuMat d_mat;

        std::cout << "Uploading 1080p frame to Jetson GPU memory..." << std::endl;

        // 5. Uploading to GPU memory exercises the hardware pipeline
        d_mat.upload(h_mat);

        std::cout << "SUCCESS: Matrix loaded into GPU VRAM!" << std::endl;
        std::cout << "GPU Matrix Dimensions: " << d_mat.cols << "x" << d_mat.rows << std::endl;
        std::cout << "========================================" << std::endl;
    } else {
        std::cout << "ERROR: OpenCV was not built with CUDA support correctly." << std::endl;
        std::cout << "========================================" << std::endl;
    }

    return 0;
}
