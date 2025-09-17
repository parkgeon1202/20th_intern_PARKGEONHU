#include "hw2.hpp"
using namespace hw2;
namespace hw2{
double sqrt_newton(double n) {     //sqrt함수를 못 사용하기에 이를 위한 근사 함수
    double y = n /2 ;     // 초기 추정값
    double difference = 0.00001;  // 허용 오차

    while (y * y - n > difference || n - y * y > difference) {
        y = (y + n / y) / 2.0;
    }

    return y;
}
}
void cal_points::put_points(P* points, int n){
        this->points = points;
        this->size=n;
}
void cal_points::calculate(){
        double max=0.0;
        double dx0 = points[0].x - points[1].x;
        double dy0 = points[0].y - points[1].y;
        double min = sqrt_newton(dx0*dx0 + dy0*dy0);
        double result=0.0;
        P max_points[2] = {points[0], points[1]};
        P min_points[2] = {points[0], points[1]};
        for(int i=0; i< size; i++ ){
            for(int j=i+1; j<size; j++){
                result = sqrt_newton((points[i].x - points[j].x)*(points[i].x - points[j].x) + (points[i].y - points[j].y)*(points[i].y - points[j].y));
                if(max< result){
                    max= result;
                    max_points[0] = points[i];
                    max_points[1] = points[j];
                };
                if(min>result){
                    min = result;
                    min_points[0] = points[i];
                    min_points[1] = points[j];
                }

            }
        }
        std::cout<<"--------Result--------"<<std::endl<<"MinDist= "<<min<<std::endl<<"Pair of Min Coor.(x,y): "<<"P1("<<min_points[0].x<<","<<min_points[0].y<<") & P2("<<min_points[1].x<<","<<min_points[1].y<<")"<<std::endl<<std::endl;
        std::cout<<"MaxDist= "<<max<<std::endl<<"Pair of Max Coor.(x,y): "<<"P1("<<max_points[0].x<<","<<max_points[0].y<<") & P2("<<max_points[1].x<<","<<max_points[1].y<<")"<<std::endl<<std::endl;
}
cal_points::cal_points():points(NULL), size(0){};
    
