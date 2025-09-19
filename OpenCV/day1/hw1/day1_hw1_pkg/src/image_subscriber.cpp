#include "image_compare.hpp"

int main()
{ 
    //객체 생성해서 필터 낀 것, 안 낀 것 비교하기 위해 메서드 각각 호출
    image_compare instance;
    instance.no_filter();
    instance.yes_filter();
    int k = waitKey(0); //waitKey() 가 없다면, 이미지를 띄우자마자 프로그램이 종료됨. 
    return 0;
}
