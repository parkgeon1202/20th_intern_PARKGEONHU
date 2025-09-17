#pragma once
#include <iostream>
namespace hw1{
class manager{
    int cnt;
    int* ptr;
    int index;
  
    
    public:
    void start();
    void get_number(int a);
    void repeat();
    void print();
    manager();
    ~manager();
};
}
