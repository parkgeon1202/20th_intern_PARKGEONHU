#include "hw3.hpp"
using namespace hw3;


int main(){
    srand((unsigned)time(NULL));
    Player player(0,0);
    Monster monster(5,4,50);
    char ch=0;
    while(end_flag){
        std::cout<<"Type Command(A/U/D/R/L/S)"<<std::endl;
        std::cin>> ch;
        if(ch=='A'){
            player.Attack(monster);
        } 
        else if(ch=='S'){
            player.Show_status();
        }
        else if(ch=='U'|| ch=='D'){
            if(ch=='U') player.Y_move(1);
            else player.Y_move(0);
        }
        else if(ch== 'L'||ch == 'R'){
           
            if(ch=='L') player.X_move(1);
            else player.X_move(0);
        }
        else{
            std::cout<<"다시 제대로 입력하세요"<<std::endl;
            
        }
        std::cin.clear(); //오류 상태 초기화
        std::cin.ignore(1000, '\n'); //버퍼에 들어간 문자 무시 
    }
    return 0;
}
