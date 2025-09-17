#include "hw2.hpp"
using namespace hw2;

int main(){
    srand((unsigned)time(NULL));
    int num=0;
    int max_coor = 0;
    int min_coor = 0;
    int nx=0;
    int ny=0;
     
    
    std::cout<<"please define the number of points: ";
    std::cin>> num;
    while(!std::cin || num<2){
            std::cout<<"잘못된 입력입니다. 다시 입력하세요"<<std::endl;
            std::cin.clear(); //오류 상태 초기화
            std::cin.ignore(1000, '\n'); //버퍼에 들어간 문자 무시 
            std::cout<<"please define the number of points: ";
            std::cin>> num; 
    }

    std::cout<<"please define the number of coor, value: ";
    std::cin >> min_coor;
    while(!std::cin){
            std::cout<<"잘못된 입력입니다. 다시 입력하세요"<<std::endl;
            std::cin.clear(); //오류 상태 초기화
            std::cin.ignore(1000, '\n'); //버퍼에 들어간 문자 무시 
            std::cout<<"please define the number of coor, value: ";
            std::cin>> min_coor; 
    }
    std::cout<<"please define the number of coor, value: ";
    std::cin >> max_coor;
    while(!std::cin || max_coor<=min_coor){
            std::cout<<"잘못된 입력입니다. 다시 입력하세요"<<std::endl;
            std::cin.clear(); //오류 상태 초기화
            std::cin.ignore(1000, '\n'); //버퍼에 들어간 문자 무시 
            std::cout<<"please define the number of coor, value: ";
            std::cin>> max_coor; 
    }
    std::cout<< "Generate Random points"<<std::endl;
    P* points = new P[num];
    for(int i=0; i< num; i++){
        nx = rand()%(max_coor-min_coor) + min_coor;
        ny = rand()% (max_coor - min_coor)+min_coor;
        std::cout<<"Point "<<i<<". nX= "<<nx;
        std::cout<<", nY= "<< ny<<std::endl;
        points[i] = P{nx, ny};
    }
    
    cal_points cal;
    cal.put_points(points, num);
    cal.calculate();
    std::cout<<"********completed*********"<<std::endl;
    delete points;

    return 0; 
}
