#include <opencv2/opencv.hpp>
using namespace cv; 
class image_compare{
    Scalar lower_green; 
    Scalar upper_green;
    Scalar lower_red_1;
    Scalar upper_red_1;
    Scalar lower_blue;
    Scalar upper_blue;
    Mat img ; 
    Mat red_mask;
    Mat blue_mask;
    Mat green_mask;
    Mat img_hsv; //이미지 담을 객체
    Mat img_blur; //필터를 적용한 blur이미지를 저장할 객체
    Mat green_blur_mask, red_blur_mask, blue_blur_mask; 
    std::string image_path;
    public:
    image_compare();
    void no_filter();
    void yes_filter();
};