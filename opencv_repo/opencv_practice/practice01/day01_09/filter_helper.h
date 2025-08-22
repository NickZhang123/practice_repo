#pragma once
#include <opencv2/opencv.hpp>
#include <cstdint>

class FilterHelper {
public:
    // 均值滤波
    static int32_t ApplyMeanBlur(const cv::Mat &src, cv::Mat &dst, int kernelSize);

    // 高斯滤波
    static int32_t ApplyGaussianBlur(const cv::Mat &src, cv::Mat &dst, int kernelSize, double sigma = 0.0);

    // 中值滤波
    static int32_t ApplyMedianBlur(const cv::Mat &src, cv::Mat &dst, int kernelSize);
};
