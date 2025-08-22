#include <opencv2/opencv.hpp>   
#include <iostream>
#include <vector>
#include "image_helper.h"
#include "edge_helper.h"
#include "plate_detector.h"
#include "hough_lane_detector.h"

using namespace std;


void CarTest()
{
    // PlateDetector pd;
    // cv::Mat image = cv::imread("../pic/car2.png");
    // cv::Mat imageAfter;
    // pd.DetectPlate(image, imageAfter);
    // cv::imshow("image", imageAfter);

    cv::Mat input = cv::imread("../pic/line_detect.jpg");
    cv::Mat output;

    HoughLaneDetector detector;
    // 设置 ROI 区域为图像下半部分的梯形
    std::vector<cv::Point> roi = {
        {100, input.rows},
        {input.cols - 100, input.rows},
        {input.cols / 2 + 50, input.rows / 2 + 50},
        {input.cols / 2 - 50, input.rows / 2 + 50}
    };
    detector.SetRoiPolygon(roi);
    detector.EnableROI(true);


    // detector.SetCannyThresholds(50, 150);
    // detector.SetHoughParams(1, CV_PI/180, 50, 50, 20);
    
    if (detector.DetectLanes(input, output) == 0) {
        cv::imshow("Lanes", output);
        cv::waitKey(0);
    } else {
        std::cerr << "车道检测失败！" << std::endl;
    }

}

void TestDay01()
{
    // 打开一张图片
    // cv::Mat imageColor = cv::imread("../pic/lenna.png");  // 默认3通道彩色加载
    // if (imageColor.empty()) {
    //     cerr << "load color image failed" << endl;
    //     return;
    // }
    // cv::imshow("imageColor", imageColor);

    // cv::Mat imageGray = cv::imread("../pic/lenna.png", cv::IMREAD_GRAYSCALE);
    // if (imageGray.empty()) {
    //     cout << "load gray img failed" << endl;
    //     return;
    // }
    // cv::imshow("image gray", imageGray);

    // cv::Mat originImage = cv::imread("../pic/lenna.png", cv::IMREAD_UNCHANGED);
    // if (originImage.empty()) {
    //     cout << "load origin image failed" << endl;
    //     return;
    // }
    // cv::imshow("origin image", originImage);

    // // 转化为灰度
    // cv::Mat transGrayImage;
    // cv::cvtColor(originImage, transGrayImage, cv::COLOR_BGR2GRAY);  // 默认是BGR
    // cv::imshow("trans gray image", transGrayImage);

    // // 保存灰度图片
    // if (!cv::imwrite("../pic/gray_lenna.png", transGrayImage)) {
    //     cout << "save gary file failed" << endl;
    //     return;
    // }

    int32_t ret = 0;

    // 颜色空间转换
    // cv::Mat lenna1;
    // ret = ImageHelper::LoadImage("../pic/lenna.png", lenna1);
    // if (ret != 0) {
    //     return;
    // }
    // ret = ImageHelper::SaveImage(lenna1, "../pic/lenna1.png");
    // if (ret != 0) {
    //     return;
    // }
    // ImageHelper::ShowImage(lenna1, "lenne");
    

    // std::vector<cv::Mat> bgr;
    // cv::split(lenna1, bgr);
    // cv::imshow("红色通道", bgr[2]);
    // cv::imshow("绿色通道", bgr[1]);
    // cv::imshow("蓝色通道", bgr[0]);

    // // 转换为HSV
    // cv::Mat hsvImage;
    // cv::cvtColor(lenna1, hsvImage, cv::COLOR_BGR2HSV);
    // cv::imshow("hsv iamge", hsvImage);

    // // 分割HSV
    // std::vector<cv::Mat> vec;
    // cv::split(hsvImage, vec);

    // // 提取H，色调通道
    // cv::Mat HueChannel = vec[0];
    // cv::imshow("hue channel", HueChannel);

    // // 提取红色区域
    // // 红色的低范围
    // cv::Mat lowerRed;
    // cv::inRange(hsvImage, cv::Scalar(0, 120, 70), cv::Scalar(10, 255, 255), lowerRed);
    // cv::imshow("lower red Area", lowerRed);

    // // 红色的高范围
    // cv::Mat upperRed;
    // cv::inRange(hsvImage, cv::Scalar(170, 120, 70), cv::Scalar(180, 255, 255), upperRed);
    // cv::imshow("high red Area", upperRed);

    // // 合并两个红色范围
    // cv::Mat redMask = lowerRed | upperRed;

    // // 显示红色区域
    // cv::imshow("Red Area", redMask);

    // // 提取绿色区域
    // cv::Mat greenMask;
    // cv::inRange(hsvImage, cv::Scalar(35, 100, 100), cv::Scalar(85, 255, 255), greenMask);
    // cv::imshow("Green Area", greenMask);

    // cv::Mat grayLennal;
    // ret = ImageHelper::ConvertGray(lenna1, grayLennal);
    // if (ret != 0) {
    //     return;
    // }
    // cv::Mat enhanced;
    // if (ImageHelper::EqualizeGrayHist(grayLennal, enhanced) == 0) 
    // {
    //     ImageHelper::ShowImage(enhanced, "enhanced image");
    // }

    // cv::Mat lenna;
    // ret = ImageHelper::LoadImage("../pic/lenna.png", lenna);
    // if (ret != 0) {
    //     return;
    // }
    // cv::imshow("orgin lennel", lenna);
    // std::cout << lenna.size[0] << "-" << lenna.size[1] << std::endl;


    // // 缩小一半
    // cv::Mat scaleImg;
    // ImageHelper::ResizeImage(lenna, scaleImg, lenna.size[0]/2, lenna.size[0]/2);
    // cv::imshow("scale-200-201", scaleImg);

    // // 放大一倍
    // ImageHelper::ResizeImage(lenna, scaleImg, lenna.size[0] * 2, lenna.size[0] * 2);
    // cv::imshow("scale-200-200", scaleImg);

    // // 旋转90度
    

    // // 旋转45度
    
    // cv::Mat rotate1;
    // ImageHelper::RotateImage(lenna, rotate1, -45);
    // cv::imshow("rotate lennel",rotate1);

    // // 翻转
    // if (ImageHelper::FlipImage(lenna, rotate1, -1) != 0) {
    //     std::cout << "error" << std::endl;
    //     return;
    // }
    // cv::imshow("flip lennel",rotate1);

    // // 剪裁
    // ImageHelper::CropImage(lenna, rotate1, cv::Rect(100, 100, 200, 200));
    // cv::imshow("crop lennel",rotate1);

    // // 图像平移，右移 50 像素，下移 30 像素
    // cv::Mat translated;
    // if (ImageHelper::TranslateImage(lenna, translated, 50, 30) == 0) {
    //     ImageHelper::ShowImage("translage", translated);
    // }


    // 滤波结果图
    // cv::Mat blurImg, gaussianImg, medianImg;
    // cv::blur(lenna, blurImg, cv::Size(5, 5));
    // cv::GaussianBlur(lenna, gaussianImg, cv::Size(5, 5), 1.5);
    // cv::medianBlur(lenna, medianImg, 5);  // 必须是奇数
    //  // 拼接显示
    // cv::Mat topRow, bottomRow, result;
    // // 第一行：原图 + 均值
    // cv::hconcat(std::vector<cv::Mat>{lenna, blurImg}, topRow);
    // // 第二行：高斯 + 中值
    // cv::hconcat(std::vector<cv::Mat>{gaussianImg, medianImg}, bottomRow);
    // // 合并两行
    // cv::vconcat(topRow, bottomRow, result);
    //  // 在图像上标注
    // cv::putText(result, "Original",       cv::Point(30, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,0,0), 2);
    // cv::putText(result, "Mean Blur",      cv::Point(lenna.cols + 30, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,0,0), 2);
    // cv::putText(result, "Gaussian Blur",  cv::Point(30, lenna.rows + 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,0,0), 2);
    // cv::putText(result, "Median Blur",    cv::Point(lenna.cols + 30, lenna.rows + 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,0,0), 2);
    //  // 显示
    // cv::imshow("滤波对比效果（上：原图+均值，下：高斯+中值）", result);


    // 边缘检测
    // cv::Mat lenna;
    // ret = ImageHelper::LoadImage("../pic/lenna.png", lenna, cv::IMREAD_GRAYSCALE);
    // if (ret != 0) {
    //     return;
    // }

    // cv::Mat sobelResult, cannyResult;
    // ret = EdgeHelper::SobelEdge(lenna, sobelResult);
    // if (ret != 0) {
    //     std::cout << "sobel edge failed" << std::endl;
    //     return;
    // } 
    // cv::imshow("Sobel Edge", sobelResult);

    // ret = EdgeHelper::CannyEdge(lenna, cannyResult, 50, 150);
    // if (ret != 0) {
    //     std::cout << "sobel edge failed" << std::endl;
    //     return;
    // }
    // cv::imshow("Canny Edge", cannyResult);
        

    // 创建一个 5x5 的二值图像，1 表示白，0 表示黑（我们用 255 和 0 表示）
    // cv::Mat input = (cv::Mat_<uchar>(5, 5) << 
    //     0, 0, 0, 0, 0,
    //     0, 1, 1, 1, 0,
    //     0, 1, 1, 1, 0,
    //     0, 1, 1, 1, 0,
    //     0, 0, 0, 0, 0);

    // // 将1转换为255，方便OpenCV操作（它识别255为白色）
    // input *= 255;  // 转换为0/255

    // // 定义输出图像
    // cv::Mat eroded;

    // // 定义结构元素（默认使用3x3全1矩阵）
    // cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    // 执行腐蚀操作
    // cv::erode(input, eroded, kernel);

     // 执行膨胀操作
    // cv::dilate(input, eroded, kernel);

     // 开运算 = 先腐蚀再膨胀
    // cv::morphologyEx(input, eroded, cv::MORPH_OPEN, kernel);

    // 闭运算 = 先膨胀再腐蚀
    // cv::morphologyEx(input, eroded, cv::MORPH_CLOSE, kernel);

    // // std::cout << "腐蚀结果：\n";
    // std::cout << "膨胀结果：\n";
    // for (int i = 0; i < eroded.rows; ++i) {
    //     for (int j = 0; j < eroded.cols; ++j) {
    //         std::cout << (eroded.at<uchar>(i, j) ? 1 : 0) << " ";
    //     }
    //     std::cout << "\n";
    // }
    /*
    腐蚀结果：
    0 0 0 0 0 
    0 0 0 0 0 
    0 0 1 0 0 
    0 0 0 0 0 
    0 0 0 0 0 

    膨胀结果：
    1 1 1 1 1 
    1 1 1 1 1 
    1 1 1 1 1 
    1 1 1 1 1 
    1 1 1 1 1 

    开运算：先腐蚀，再膨胀
    0 0 0 0 0 
    0 1 1 1 0 
    0 1 1 1 0 
    0 1 1 1 0 
    0 0 0 0 0 

    闭运算；先膨胀，在腐蚀
    1 1 1 1 1 
    1 1 1 1 1 
    1 1 1 1 1 
    1 1 1 1 1 
    1 1 1 1 1 
    */

   CarTest();
    return;
}
