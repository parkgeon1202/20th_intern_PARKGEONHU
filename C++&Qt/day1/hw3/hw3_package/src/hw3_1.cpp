#include "hw3.hpp"
using namespace hw3;
namespace hw3{
   int end_flag=1;   
   int absolute(int n){
    if(n>=0) return n;
    else if(n<0) return -n;
    else return 0;
   }
}



Monster::Monster():x(0), y(0), HP(50){};
Monster::Monster(int x, int y, int HP): x(x), y(y), HP(HP){};
int Monster:: Be_Attacked(){
    HP-=10;
    y++; //맞으면 뒤로 물러남
    return HP;
}

Player::Player(){x=0;  y=0; HP=30; MP=10;};
Player::Player(int x, int y):x(x), y(y), HP(30), MP(10){};
void Player::X_move(int move){
    switch(move){
        case 1:
        x--;
        std::cout<<"X Position -1 moved!"<<std::endl;
        break;
        case 0:
        x++;
        std::cout<<"X Position 1 moved!"<<std::endl;
        break;
    }
}
void Player::Y_move(int move){
    switch(move){
        case 1:
        y++;
        std::cout<<"Y Position 1 moved!"<<std::endl;
        break;
        case 0:
        y--;
        std::cout<<"Y Position -1 moved!"<<std::endl;
        break;
    }
}
void Player::Attack(Monster& target){
    if(absolute(target.x-x)<=1 && absolute(target.y-y)<=1){ //좌표상 거리가 1이하일 때, 즉 근접할 때
        int monster_HP = target.Be_Attacked();
        MP--;
        std::cout<<"공격 성공!"<<std::endl<<"남은 체력: "<< monster_HP<<std::endl;
        if(monster_HP==0){
            std::cout<<"Monster_die!"<<std::endl;
            end_flag=0;
        }
    }
    else{
        std::cout<< "공격 실패!"<<std::endl;
        MP--;
    }
    if(MP==0){
        std::cout<<"MP 부족!"<<std::endl;
        end_flag=0;
    }
}
void Player:: Show_status(){
    std::cout<< "HP: "<< HP<<std::endl<<"MP: "<<MP<<std::endl<<"Position: "<<x<<", "<< y<<std::endl;
}
