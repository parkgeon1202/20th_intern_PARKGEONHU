//#pragma once
#include <iostream>
#include <ctime>
namespace hw3{
extern int end_flag;
int absolute(int n);
class Monster{
    
    public:
    int HP;
    int x;
    int y;
    Monster();
    Monster(int x, int y, int HP);
    int Be_Attacked();

};
class Player{
    
   
    public:
    int MP;
    int x;
    int y;
    int HP;
    Player();
    Player(int x, int y);
    void X_move(int move);
    void Y_move(int move);
    void Attack(Monster& target);
    void Show_status();
};
}
