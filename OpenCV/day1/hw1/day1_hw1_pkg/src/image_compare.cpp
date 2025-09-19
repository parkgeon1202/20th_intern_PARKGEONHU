#include "image_compare.hpp"
 //Scalar를 통해 rgb혹은  hsv값 범위 설정함
image_compare:: image_compare():lower_green(35, 50, 50), upper_green(85, 255, 255), lower_red_1(0, 50, 50), 
upper_red_1(10, 255, 255), lower_blue(100, 50, 50), upper_blue(130, 255, 255){
    image_path = "/home/geonhu/colcon_ws/src/day1_hw1_pkg/resources/test.png"; //사진 파일의 절대 경로
    img = imread(image_path, IMREAD_COLOR); //imread() 메서드를 통해 사진 객체 불러옴

   
  
}
void image_compare:: no_filter(){ //hsv적용하며 필터 안 긴 상태의 바이너리 이미지 파일 출력
    cvtColor(img, img_hsv, COLOR_BGR2HSV);
    //hsv이미지에서부터 해당 범위 내에 있는 부분을 바이너리 이미지로 가져옴
    inRange(img_hsv, lower_green, upper_green, green_mask);
    inRange(img_hsv, lower_red_1, upper_red_1, red_mask);
    inRange(img_hsv, lower_blue, upper_blue, blue_mask);
    //이미지를 보여줌
    imshow("HSV Image", img_hsv);
    imshow("Green Mask", green_mask);
    imshow("Red Mask", red_mask);
    imshow("Blue Mask", blue_mask);
}
void image_compare::yes_filter(){
    GaussianBlur(img, img_blur, Size(19,19), (double)5);//가우시안blur 필터 사용
   
    cvtColor(img_blur, img_hsv, COLOR_BGR2HSV); //img_hsv얻어옴
    inRange(img_hsv, lower_green, upper_green, green_blur_mask); //필터 적용한 상태로 바이너리 이미지 가져옴
    inRange(img_hsv, lower_red_1, upper_red_1, red_blur_mask);
    inRange(img_hsv, lower_blue, upper_blue, blue_blur_mask);
    imshow("HSV Image", img_hsv); 
    imshow("Green_blur_Mask", green_blur_mask);
    imshow("blue_blur_Mask", blue_blur_mask);
    imshow("Red_blur_Mask", red_blur_mask);
}