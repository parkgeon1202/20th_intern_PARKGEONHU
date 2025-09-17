#include "hw1.hpp"
using namespace hw1;
void manager::start(){
        std::cout<<"몇 개의 원소를 할당하겠습니까? : ";
        std::cin>>  cnt;
        if(!std::cin || cnt<1){
            std::cout<<"잘못된 입력입니다. 다시 입력하세요"<<std::endl;
            std::cin.clear(); //오류 상태 초기화
            std::cin.ignore(1000, '\n'); //버퍼에 들어간 문자 무시
            manager::start();
        }
        else ptr = new int[cnt];
    }
void manager:: get_number(int a){
       ptr[index] = a;
       this->index++; 
}
void manager:: repeat(){
        int input=0;
      for(int i=0; i< cnt; i++){
        std::cout<<"정수형 데이터 입력: ";
        std::cin>>  input;
        if(!std::cin){
            std::cout<<"잘못된 입력입니다. 다시 입력하세요"<<std::endl;
            std::cin.clear(); //오류 상태 초기화
            std::cin.ignore(1000, '\n'); //버퍼에 들어간 문자 무시
            i--;
            continue;
        }
        get_number(input);
      }
}
void manager:: print(){
        int min= ptr[0];
        int max= ptr[0];
        int sum =0;
        for(int i=0; i< cnt; i++){
            sum+= ptr[i];
            if(min>ptr[i]){
                min=ptr[i];
            }
            if(max < ptr[i]){
                max= ptr[i];
            }
        }
        double avg= (double)sum/ cnt;
        std::cout<<"최대값: "<< max <<std::endl<<"최소값: "<< min<< std::endl<< "전체 합: "<< sum<< std::endl<< "평균: "<< avg<<std::endl;
}
manager::manager():cnt(0), ptr(NULL), index(0){};
manager::~manager(){
        delete[] ptr;
}