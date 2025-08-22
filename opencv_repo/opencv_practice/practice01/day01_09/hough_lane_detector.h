#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class HoughLaneDetector {
public:
    HoughLaneDetector();

    // 设置 Canny 边缘检测的上下阈值
    void SetCannyThresholds(int low, int high);

    // 设置霍夫直线变换的参数
    void SetHoughParams(double rho, double theta, int threshold, double minLineLength, double maxLineGap);

    // 启用 / 禁用 ROI 裁剪
    void EnableROI(bool enable);

    // 新增函数：设置 ROI 区域（用 4 个顶点定义多边形）
    void SetRoiPolygon(const std::vector<cv::Point>& roiPolygon);

    // 主函数：输入原图，输出标记车道线的图像
    int32_t DetectLanes(const cv::Mat& inputImage, cv::Mat& outputImage);

private:
    int _cannyLowThreshold;
    int _cannyHighThreshold;

    double _houghRho;       // 距离分辨率（像素单位）
    double _houghTheta;     // 角度分辨率（弧度）
    int _houghThreshold;    // 投票累积阈值（越大只保留越明显的直线）
    double _minLineLength;  // 最小直线长度
    double _maxLineGap;     // 最大允许的线段中断（像素）

    bool _enableRoi;
    std::vector<cv::Point> _roiPolygon;
};