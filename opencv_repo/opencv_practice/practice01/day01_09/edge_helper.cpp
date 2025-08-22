#include "edge_helper.h"

int32_t EdgeHelper::SobelEdge(const cv::Mat &inputImage, cv::Mat &outputImage, int32_t ksize)
{
    if (inputImage.empty() || inputImage.channels() != 1) {
        return -1;
    }
        
    cv::Mat gradX, gradY;
    cv::Sobel(inputImage, gradX, CV_64F, 1, 0, ksize);
    cv::Sobel(inputImage, gradY, CV_64F, 0, 1, ksize);

    cv::Mat magnitude;
    cv::magnitude(gradX, gradY, magnitude);
    magnitude.convertTo(outputImage, CV_8U);

    return 0;
}

int32_t EdgeHelper::CannyEdge(const cv::Mat &inputImage, cv::Mat &outputImage, double threshold1, double threshold2)
{
    if (inputImage.empty() || inputImage.channels() != 1) {
        return -2;
    }
        
    cv::Canny(inputImage, outputImage, threshold1, threshold2);
    
    return 0;
}