#include "IImageProcessor.hpp"
extern IImageProcessor* createCPUImageProcessor();
#ifdef ARCHITECTURE_JETSONNANO
extern "C" IImageProcessor* createGPUImageProcessor();
#endif
int main() {
    cv::Mat input_frame = cv::Mat::zeros(1080, 1920, CV_8UC1);
    cv::circle(input_frame, cv::Point(960, 540), 300, cv::Scalar(255), -1);

    cv::imwrite("input.png", input_frame);
    cv::Mat cpu_output_frame;

    auto cpu_processor = createCPUImageProcessor();
    if (cpu_processor == nullptr) {
        std::cout << "CPU Processor NULL!" << std::endl;
        return 1;
    }

    cpu_processor->processFrame(input_frame, cpu_output_frame);
    cv::imwrite("cpu_output.png", cpu_output_frame);
#ifdef ARCHITECTURE_JETSONNANO
    cv::Mat gpu_output_frame;
    auto gpu_processor = createGPUImageProcessor();
    if (gpu_processor == nullptr) {
        std::cout << "CPU Processor NULL!" << std::endl;
        return 1;
    }

    gpu_processor->processFrame(input_frame, gpu_output_frame);
    cv::imwrite("gpu_output.png", gpu_output_frame);
#endif
    return 0;
}
