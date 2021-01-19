#include <iostream>
#include <math.h>
#include "Bod2D.h"


int main() {

    Bod2D A(3.0f,3);
    Bod2D B(-3.0f,-2);
    std::cout<< "Vzdialenost A a B je: " << A.distance(B)<< std::endl;
    std::cout<< "Vzdialenost bodov je: " <<A.distanceFromBase() << std::endl;
    A.centerOfLine(B);
    std::cout<< 2*A << std::endl;
    std::cout<< A*2 << std::endl;
    std::cout<< A-B << std::endl;
    std::cout<< A+B << std::endl;
    std::cout<< A/2 << std::endl;



    return 0;
}

Bod2D::Bod2D()
{
    std::cout<<"Zadaj suradnicu 'x' a 'y': " << std::flush;
    std::cin>>x>>y;
}

Bod2D::Bod2D(char coordinatesType, float myCoordinates)
{
    switch(coordinatesType)
    {
        case 'x':
            {
                x=myCoordinates;
                std::cout<<"Zadaj suradnicu 'y' bodu: " << std::endl;
                std::cin>>y;
                break;
            }
        case 'y':
            {
                y=myCoordinates;
                std::cout<<"Zadaj suradnicu 'x' bodu: " << std::endl;
                std::cin>>x;
                break;
            }
        default:
        {
            x = 0;
            y = 0;
            std::cout<<"Zadana neznama suradnica. Bod ma hodnotu [0,0]" <<std::endl;
            break;
        }
    }

}



Bod2D::Bod2D(float myX,float myY):x(myX),y(myY) {}


std::ostream & operator<<(std::ostream &os, const Bod2D &point)
{
   os << "[" << point.x << "," << point.y << "]";
   return os;
}

std::istream & operator>>(std::istream &is, Bod2D &point)
{
    is >> point.x >> point.y;
    return is;
}

Bod2D Bod2D::operator+(const Bod2D &point1) const
{
    return {x+point1.x,y+point1.y};
}

Bod2D Bod2D::operator-(const Bod2D &point1) const
{
    return {x-point1.x,y-point1.y};
}

Bod2D Bod2D::operator*(float  number) const
{
    return {x*number,y*number};
}

Bod2D operator*(float  number, Bod2D &point1)
{
    return {number*point1.x,number*point1.y};
}

Bod2D Bod2D::operator/(float number) const
{
    if(number==0)
    {
        number= 1;
        std::cout<< "Delit nulou nemozno, preto suradnice bodu ostavaju nezmene."<< std::endl;
    }
    return {x/number,y/number};
}


float Bod2D::distance(const Bod2D &point1)
{
    Bod2D differenceP(x > 0 ? x-point1.x : point1.x-x, y >0 ? y-point1.y : point1.y-y);
    return sqrt(differenceP.x*differenceP.x + differenceP.y*differenceP.y);
}

float Bod2D::distanceFromBase() const
{
    return sqrt(x*x + y*y);
}
void Bod2D::centerOfLine( const Bod2D & point1)
{
    Bod2D point(x+point1.x,y+point1.y);
    std::cout<< "Stred usecky je v bode: " << point/2 << std::endl;

}
