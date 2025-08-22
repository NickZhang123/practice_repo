#include "plate_detector.h"

// 传入彩色图像，返回检测标记图（画出车牌矩形）
// 返回0表示正常，<0表示失败
int32_t PlateDetector::DetectPlate(cv::Mat &imgBgr, cv::Mat &imgResult) 
{
    if (imgBgr.empty()) {
        return -1;
    }

    // 1. 灰度转换
    cv::Mat gray;
    cv::cvtColor(imgBgr, gray, cv::COLOR_BGR2GRAY);

    // 2. 高斯滤波去噪
    cv::Mat blurImg;
    cv::GaussianBlur(gray, blurImg, cv::Size(5, 5), 0);

    // 3. Canny边缘检测
    cv::Mat edges;
    cv::Canny(blurImg, edges, 100, 200);
    cv::imshow("edges", edges);

    // 4. 形态学闭运算连接边缘
    cv::Mat morphImg;
    cv::morphologyEx(edges, morphImg, cv::MORPH_CLOSE, _morphKernel);
    cv::imshow("morphImg", morphImg);

    // 5. 轮廓查找
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(morphImg, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 6. 筛选合适车牌轮廓
    imgResult = imgBgr.clone();
    bool foundPlate = false;
    for (const auto &contour : contours) {
        // 忽略点数太少的轮廓
        if (contour.size() < 50) {
            continue; 
        }

        // 找最小外接旋转矩阵
        cv::RotatedRect rect = cv::minAreaRect(contour);

        // 长宽比过滤，车牌一般比例约2~6
        float w = rect.size.width;
        float h = rect.size.height;
        float ratio = w > h ? w / h : h / w;
        if (ratio < 2.0f || ratio > 6.0f) {
            continue;
        }

        // 面积过滤，忽略太小的区域
        // 宽度范围（100~400），高度（20~100）
        if (w * h < 1000) {
            continue;
        }

        // 绘制矩形
        cv::Point2f points[4];
        rect.points(points);
        for (int i = 0; i < 4; ++i) {
            cv::line(imgResult, points[i], points[(i+1)%4], cv::Scalar(0, 255, 0), 2);
        }

        foundPlate = true;
    }

    return foundPlate ? 0 : -2;
}