#include <opencv2/opencv.hpp>
#include <vector>

class PlateDetector {
public:
    PlateDetector() {
        // 初始化结构元素大小，可根据需求调整
        _morphKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(20, 5));
    }

    // 检测车牌矩形区域
    int32_t DetectPlate(cv::Mat &imgBgr, cv::Mat &imgResult);

private:
    cv::Mat _morphKernel;
};