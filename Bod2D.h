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

    Bod2D operator+(const Bod2D &point1) const;
    Bod2D operator-(const Bod2D &point1) const;
    Bod2D operator*(float number) const; // bod * cislo
    friend Bod2D operator*(float  number, Bod2D &point1); //cislo * bod
    Bod2D operator/( float number) const;

    double distance(const Bod2D &point1 = Bod2D(0.0f,0) ) const;
    Bod2D centerOfLine(const Bod2D & point1) const;


    class OpenFileCheck
    {
    private:
        const char * msg;
    public:
        OpenFileCheck(const char * currentMsg):msg(currentMsg){};
        void getMsg() const;
    };

};

class Line
{
private:
    Bod2D basePoint;
    Bod2D endPoint;
    double length = basePoint.distance(endPoint);
public:
    explicit Line(  Bod2D  myBasePoint = Bod2D(0.0f, 0.0f),  Bod2D  myEndPoint = Bod2D(1.0f, 0.0f));

    friend std::ostream & operator<<(std::ostream &os, const Line & line);
    friend std::istream & operator>>(std::istream &is, Line & line);

    bool operator<(Line & line1);

    static void getDistanceFromFile (std::ifstream & fin,const char * fileName, Line arr[] );
    static void getSortedDistance(std::ofstream & fout, const char * fileName, Line arr[], int numberOfElements);
};


#endif //BOD_BOD2D_H
