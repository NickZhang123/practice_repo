#include "filter_helper.h"

int32_t FilterHelper::ApplyMeanBlur(const cv::Mat &src, cv::Mat &dst, int kernelSize) 
{
    if (src.empty() || kernelSize <= 1) {
        return -1;
    }
    cv::blur(src, dst, cv::Size(kernelSize, kernelSize));
    return 0;
}

int32_t FilterHelper::ApplyGaussianBlur(const cv::Mat &src, cv::Mat &dst, int kernelSize, double sigma) 
{
    if (src.empty() || kernelSize % 2 == 0 || kernelSize <= 1) {
        return -1;
    }
    cv::GaussianBlur(src, dst, cv::Size(kernelSize, kernelSize), sigma);
    return 0;
}

int32_t FilterHelper::ApplyMedianBlur(const cv::Mat &src, cv::Mat &dst, int kernelSize) 
{
    if (src.empty() || kernelSize % 2 == 0 || kernelSize <= 1) {
        return -1;
    }
    cv::medianBlur(src, dst, kernelSize);
    return 0;
}