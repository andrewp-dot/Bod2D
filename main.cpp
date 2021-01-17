#include <iostream>
#include <math.h>
#include "Bod2D.h"


int main() {

    Bod2D A(3.0f,4);
    Bod2D B(-2.0f,2);
    std::cout<< "distance is: " << Bod2D::distance(B,A)<< std::endl;
    std::cout<< "distance from base is: " << Bod2D::distanceFromBase(A);
    Bod2D::centerOfLine(A,B);



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

Bod2D operator+(Bod2D &point1, Bod2D &point2)
{
    return {point1.x+point2.x,point1.y+point2.y};
}

Bod2D operator-(Bod2D &point1, Bod2D &point2)
{
    return {point1.x-point2.x,point1.y-point2.y};
}

Bod2D operator*(Bod2D &point1, float  number)
{
    return {point1.x*number,point1.y*number};
}

Bod2D operator*(float  number, Bod2D &point1)
{
    return {number*point1.x,number*point1.y};
}

Bod2D operator/(Bod2D &point1, float number)
{
    if(number==0)
    {
        number= 1;
        std::cout<< "Delit nulou nemozno, preto suradnice bodu ostavaju nezmene."<< std::endl;
    }
    return {point1.x/number,point1.y/number};
}

Bod2D operator/(float number, Bod2D &point1)
{
    if(point1.x==0 or point1.y)
    {
        number= 1;
        std::cout<< "Delit nulou nemozno, preto suradnice bodu ostavaju nezmene."<< std::endl;
    }
    return {number/point1.x,number/point1.y};
}

float Bod2D::distance(const Bod2D &point1,const Bod2D &point2)
{
    Bod2D differenceP(point2.x > 0 ? point1.x-point2.x : point2.x-point1.x,point2.y >0 ? point1.y-point2.y : point2.y-point1.y);
    return sqrt(differenceP.x*differenceP.x + differenceP.y*differenceP.y);
}

float Bod2D::distanceFromBase(const Bod2D point)
{
    return sqrt(point.x*point.x + point.y*point.y);
}
void Bod2D::centerOfLine( Bod2D point1, Bod2D point2)
{
    Bod2D point = point1+point2;
    std::cout<< "stred usecky je v bode: " << point/2 << std::endl;

}
