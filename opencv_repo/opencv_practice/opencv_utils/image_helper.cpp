#include "image_helper.h"

int32_t ImageHelper::LoadImage(const std::string &loadPath, cv::Mat &image, int flag)
{
    image = cv::imread(loadPath, flag);
    if (image.empty()) {
        std::cerr << "[Error] Failed to load image: " << loadPath << std::endl;
        return -1;
    }

    return 0;
}

int32_t ImageHelper::SaveImage(const cv::Mat &image, const std::string &savePath)
{
    if (image.empty()) {
        std::cerr << "[Error] Empty image, cannot save." << std::endl;
        return -1;
    }
    bool success = cv::imwrite(savePath, image);
    if (!success) {
        std::cerr << "[Error] Failed to save image: " << savePath << std::endl;
        return -1;
    }

    return 0;
}

void ImageHelper::ShowImage(const std::string &winName, const cv::Mat &image)
{
    if (image.empty()) {
        std::cerr << "[Error] Empty image, cannot show." << std::endl;
        return;
    }

    cv::imshow(winName, image);

    return;
}


int32_t ImageHelper::ConvertGray(const cv::Mat &image, cv::Mat &tgtImage)
{
    if (image.empty()) {
        std::cerr << "[Error] Empty image, cannot convert." << std::endl;
        return -1;
    }

    cv::cvtColor(image, tgtImage, cv::COLOR_BGR2GRAY);

    return 0;
}

int32_t ImageHelper::ConvertToHSV(const cv::Mat &src, cv::Mat &hsv) 
{
    if (src.empty()) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
    return 0;
}

int32_t ImageHelper::ConvertToLab(const cv::Mat &src, cv::Mat &lab) 
{
    if (src.empty()) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }
    cv::cvtColor(src, lab, cv::COLOR_BGR2Lab);
    return 0;
}

int32_t ImageHelper::ConvertToYCrCb(const cv::Mat &src, cv::Mat &ycrcb) 
{
    if (src.empty()) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }
    cv::cvtColor(src, ycrcb, cv::COLOR_BGR2YCrCb);
    return 0;
}

int32_t ImageHelper::SplitChannels(const cv::Mat &src, std::vector<cv::Mat> &channels) 
{
    if (src.empty()) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }
    cv::split(src, channels);
    return 0;
}

int32_t ImageHelper::MergeChannels(const std::vector<cv::Mat> &channels, cv::Mat &dst) 
{
    if (channels.empty()) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }
    cv::merge(channels, dst);
    return 0;
}

int32_t ImageHelper::ExtractColorRangeHSV(const cv::Mat &src, const cv::Scalar &lower, const cv::Scalar &upper, cv::Mat &mask) 
{
    if (src.empty()) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }
    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
    cv::inRange(hsv, lower, upper, mask);
    return 0;
}

int32_t ImageHelper::EqualizeGrayHist(const cv::Mat &gray, cv::Mat &enhanced) 
{
    if (gray.empty() || gray.channels() != 1) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }
    cv::equalizeHist(gray, enhanced);
    return 0;
}

int32_t ImageHelper::ThresholdBinary(const cv::Mat &gray, cv::Mat &bin, double thresh) 
{
    if (gray.empty() || gray.channels() != 1) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }

    cv::threshold(gray, bin, thresh, 255, cv::THRESH_BINARY);
    return 0;
}

int32_t ImageHelper::AdaptiveThreshold(const cv::Mat &gray, cv::Mat &bin) 
{
    if (gray.empty() || gray.channels() != 1) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }

    cv::adaptiveThreshold(gray, bin, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2);
    return 0;
}

int32_t ImageHelper::ResizeImage(const cv::Mat &src, cv::Mat &dst, int width, int height, int interpolation) 
{
    if (src.empty()) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }

    cv::resize(src, dst, cv::Size(width, height), 0, 0, interpolation);
    return 0;
}

int32_t ImageHelper::RotateImage(const cv::Mat &src, cv::Mat &dst, double angle)
{
    /*
    步骤
        1. 计算旋转中心
        2. 根据旋转中心和旋转角度计算旋转矩阵
        3. 计算旋转后的长、宽
        4. 通过旋转矩阵，移动旋转后的中心点，使得其能显示在新的中心点
    */
    if (src.empty()) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }

    // 计算旋转中心
    // 如果没有明确指定旋转中心，默认的旋转中心是图像的 (0,0) 点，图像的左上角。如果要进行中心旋转，旋转中心应该是图像的几何中心。
    // 这一步确保旋转不会造成图像的扭曲或错位
    cv::Point2f center(src.cols / 2.0F, src.rows / 2.0F);

    // 获取旋转矩阵(旋转中心center、旋转角度angle 和缩放因子1.0)
    // angle:顺时针旋转是负值，逆时针旋转是正值
    // 1.0：表示没有缩放
    cv::Mat rotMat = cv::getRotationMatrix2D(center, angle, 1.0);   // 生成旋转变换的矩阵

    // 计算旋转后的包围框
    // 旋转操作本质上改变了图像的形状，尤其是如果角度较大时，旋转后的图像会变成一个倾斜的矩形
    // 直接应用旋转矩阵可能会导致旋转后的图像部分被裁剪掉。为了解决这个问题，需要计算出旋转后的图像的 最小矩形边界，即包含图像所有旋转部分的矩形区域。这样可以保证旋转后的图像完整显示。
    cv::Rect bbox = cv::RotatedRect(center, src.size(), angle).boundingRect();

    // 调整旋转矩阵以避免裁剪(通过调整平移量，我们可以确保旋转后的图像仍然在输出图像的中央，并且不会被裁剪)
    // 在进行旋转时，图像的中心可能不再保持在图像的中心位置。旋转矩阵是基于旋转中心计算的，但旋转后，图像的包围框会发生变化，旋转后的图像会向外扩展，导致图像在平移时出现偏移。
    // rotMat.at<double>(0, 2) 和 rotMat.at<double>(1, 2) 分别表示旋转矩阵的平移部分（tx 和 ty）
    //      它们的值是旋转矩阵中的第三列元素（即平移量）。  -- 确保旋转后的图像水平对齐到新的中心位置。
    // bbox.width / 2.0 - center.x 和 bbox.height / 2.0 - center.y 是对旋转后图像的平移修正，
    //      使得旋转后的图像能够在新图像尺寸中居中。        -- 确保旋转后的图像垂直对齐到新的中心位置。
    // 这个操作的目标是让旋转后的图像在没有被裁剪的情况下完全显示出来，保持图像的完整性。
    rotMat.at<double>(0, 2) += bbox.width / 2.0 - center.x;     
    rotMat.at<double>(1, 2) += bbox.height / 2.0 - center.y;  
    // rotMat.at<double>(0, 2) 是用于访问和修改旋转矩阵的平移部分; cv::getRotationMatrix2D(center, angle, scale) 函数生成的 旋转矩阵（rotMat）是一个 2x3 的矩阵
    /*
        cos(θ)  −sin(θ) tx
        sin(θ)  cos(θ)  ty
​           θ 是旋转角度（以度为单位），tx/ty是平移量
    */

    // 应用旋转变换
    cv::warpAffine(src, dst, rotMat, bbox.size());
    return 0;
}

int32_t ImageHelper::FlipImage(const cv::Mat &src, cv::Mat &dst, int flipCode) 
{
    if (src.empty()) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    } 

    if (flipCode != 0 && flipCode != 1 && flipCode != -1) {
        return -2;
    }

    cv::flip(src, dst, flipCode);

    return 0;
}

int32_t ImageHelper::CropImage(const cv::Mat &src, cv::Mat &dst, const cv::Rect &roi) 
{
    if (src.empty()) {
        std::cerr << "[Error] Empty image" << std::endl;
        return -1;
    }

    if (roi.x < 0 || roi.y < 0 || roi.x + roi.width > src.cols || roi.y + roi.height > src.rows) {
        return -2;  // ROI 越界
    }
        
    dst = src(roi).clone();

    return 0;
}

int32_t ImageHelper::TranslateImage(const cv::Mat &src, cv::Mat &dst, int dx, int dy) 
{
    if (src.empty()) {
        return -1;
    }

    // 构造平移矩阵(2*3)
    // 移动后出现的空白区域由 OpenCV 默认填充为黑色；
    cv::Mat transMat = (cv::Mat_<double>(2, 3) << 1, 0, dx,
                                                  0, 1, dy);
    // 平移矩阵说明：2x3仿射变换矩阵，实现平移、旋转、缩放
    /**
     *  M = | a  b  tx |        // a、b：控制缩放、旋转、剪切。  tx, x方向平移量
            | c  d  ty |        // c、d：控制旋转、剪切、反射。  ty, y方向平移量
        应用这个矩阵，对每个点(x', y')应用如下公式做转换；大学里面的几何数学
            x = a * x' + b * y' + tx; 
            y = c * x' + d * y' + ty;
     */


    // warpAffine 应用变换
    cv::warpAffine(src, dst, transMat, src.size());

    return 0;
}