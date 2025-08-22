#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat image = cv::Mat::zeros(100, 100, CV_8UC3); // 创建一个黑图
    if (image.empty()) {
        std::cerr << "Failed to create image" << std::endl;
        return -1;
    }
    cv::circle(image, cv::Point(50, 50), 30, cv::Scalar(0, 255, 0), -1);
    cv::imshow("Test", image);
    cv::waitKey(0);
    return 0;
}
