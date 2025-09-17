#include <iostream>
#include <cstdlib>
#include <ctime>
namespace hw2{
double sqrt_newton(double n);

typedef struct point{
    int x;
    int y;
}P;
class cal_points{

    P* points;
    int size;
    
    public:
    void put_points(P* points, int n);
    void calculate();
    cal_points();
    
};
}
