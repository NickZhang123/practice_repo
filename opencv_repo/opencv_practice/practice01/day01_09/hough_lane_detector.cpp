#include "hough_lane_detector.h"

HoughLaneDetector::HoughLaneDetector()
    : _cannyLowThreshold(50), _cannyHighThreshold(150),
      _houghRho(1), _houghTheta(CV_PI / 180),
      _houghThreshold(50), _minLineLength(50), _maxLineGap(10),
      _enableRoi(true) // 默认启用 ROI
{

}

void HoughLaneDetector::SetCannyThresholds(int low, int high) 
{
    _cannyLowThreshold = low;
    _cannyHighThreshold = high;
}

void HoughLaneDetector::SetHoughParams(double rho, double theta, int threshold, double minLineLength, double maxLineGap) 
{
    _houghRho = rho;
    _houghTheta = theta;
    _houghThreshold = threshold;
    _minLineLength = minLineLength;
    _maxLineGap = maxLineGap;
}

void HoughLaneDetector::EnableROI(bool enable) 
{
    _enableRoi = enable;
}

// 设置 ROI 多边形
void HoughLaneDetector::SetRoiPolygon(const std::vector<cv::Point>& roiPolygon) 
{
    _roiPolygon = roiPolygon;
}

int32_t HoughLaneDetector::DetectLanes(const cv::Mat& inputImage, cv::Mat& outputImage) 
{
    // 输入图像为空，直接返回错误码
    if (inputImage.empty()) {
        return -1;
    }

    // 第1步：转换为灰度图
    cv::Mat gray;
    cv::cvtColor(inputImage, gray, cv::COLOR_BGR2GRAY);

    // 第2步：高斯滤波，降噪
    cv::Mat blurred;
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);

    // 第3步：Canny 边缘检测
    cv::Mat edges;
    cv::Canny(blurred, edges, _cannyLowThreshold, _cannyHighThreshold);

    // 如果启用 ROI 裁剪
    if (_enableRoi && !_roiPolygon.empty()) {
        // 创建与图像同大小的黑色 mask
        cv::Mat mask = cv::Mat::zeros(edges.size(), CV_8UC1);
        // 填充多边形区域为白色（255）
        std::vector<std::vector<cv::Point>> pts = { _roiPolygon };
        cv::fillPoly(mask, pts, 255);
        // 用 mask 过滤 edges
        cv::bitwise_and(edges, mask, edges);
    }

    // 第4步：霍夫直线变换，提取直线段
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(edges, lines,
                    _houghRho, _houghTheta, _houghThreshold,
                    _minLineLength, _maxLineGap);

    // 第5步：绘制直线
    outputImage = inputImage.clone();
    for (const auto& line : lines) {
        cv::Point pt1(line[0], line[1]);
        cv::Point pt2(line[2], line[3]);
        cv::line(outputImage, pt1, pt2, cv::Scalar(0, 255, 0), 2);  // 绿色线段
    }

    return 0; // 正常完成
}