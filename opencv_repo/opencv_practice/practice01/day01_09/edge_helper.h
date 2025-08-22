#pragma once

#include <opencv2/opencv.hpp>

class EdgeHelper
{
public:
   
    static int32_t SobelEdge(const cv::Mat &inputImage, cv::Mat &outputImage, int32_t ksize = 3);

    static int32_t CannyEdge(const cv::Mat &inputImage, cv::Mat &outputImage, double threshold1, double threshold2);
};