#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class ImageHelper {
public:
    // 基础功能
    static int32_t LoadImage(const std::string &loadPath, cv::Mat &image, int flag = cv::IMREAD_COLOR);
    static int32_t SaveImage(const cv::Mat &image, const std::string &savePath);
    static void ShowImage(const std::string &winName, const cv::Mat &image);

    // 灰度转换
    static int32_t ConvertGray(const cv::Mat &image, cv::Mat &tgtImage);
    
    // 彩色颜色空间转换
    static int32_t ConvertToHSV(const cv::Mat &src, cv::Mat &hsv);
    static int32_t ConvertToLab(const cv::Mat &src, cv::Mat &lab);
    static int32_t ConvertToYCrCb(const cv::Mat &src, cv::Mat &ycrcb);

    // 通道
    static int32_t SplitChannels(const cv::Mat &src, std::vector<cv::Mat> &channels);
    static int32_t MergeChannels(const std::vector<cv::Mat> &channels, cv::Mat &dst);
    
    // HSV提取颜色范围（如红色、绿色）
    static int32_t ExtractColorRangeHSV(const cv::Mat &src, const cv::Scalar &lower, const cv::Scalar &upper, cv::Mat &mask);

    // 灰度图直方图均衡化（提升对比度）
    static int32_t EqualizeGrayHist(const cv::Mat &gray, cv::Mat &enhanced);

    // 二值化处理
    static int32_t ThresholdBinary(const cv::Mat &gray, cv::Mat &bin, double thresh = 128);
    static int32_t AdaptiveThreshold(const cv::Mat &gray, cv::Mat &bin);

    // 图像平移（dx: 横向位移, dy: 纵向位移）
    static int32_t TranslateImage(const cv::Mat &src, cv::Mat &dst, int dx, int dy);

    // 图像操作（缩放、旋转、翻转、剪裁）
    static int32_t ResizeImage(const cv::Mat &src, cv::Mat &dst, int width, int height, int interpolation = cv::INTER_LINEAR);
    static int32_t RotateImage(const cv::Mat &src, cv::Mat &dst, double angle);         // 图像旋转（角度单位：度，正数为逆时针）
    static int32_t FlipImage(const cv::Mat &src, cv::Mat &dst, int flipCode);           // 图像翻转（flipCode: 0=上下，1=左右，-1=上下左右）
    static int32_t CropImage(const cv::Mat &src, cv::Mat &dst, const cv::Rect &roi);    // 图像裁剪（ROI 区域）

};