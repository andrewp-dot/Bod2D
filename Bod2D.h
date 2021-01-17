//
// Created by Adrián on 15.1.2021.
//

#ifndef BOD_BOD2D_H
#define BOD_BOD2D_H


class Bod2D {
private:
    float x;
    float y;
public:
    Bod2D();
    Bod2D(char coordinatesType, float myCoordinates);
    Bod2D(float myX, float myY);
    friend std::ostream & operator<<(std::ostream &os, const Bod2D &point);
    friend std::istream & operator>>(std::istream &is, Bod2D &point);
    friend Bod2D operator+(Bod2D &point1, Bod2D &point2);
    friend Bod2D operator-(Bod2D &point1, Bod2D &point2);
    friend Bod2D operator*(Bod2D &point1, float  number);
    friend Bod2D operator*(float  number, Bod2D &point1);
    friend Bod2D operator/(Bod2D &point1, float number);
    friend Bod2D operator/(float number, Bod2D &point1);
    static float distance(const Bod2D &point1,const Bod2D &point2);
    static float distanceFromBase(const Bod2D point);
    static void centerOfLine( Bod2D point1, Bod2D point2);



};


#endif //BOD_BOD2D_H
