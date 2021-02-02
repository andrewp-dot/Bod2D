#include <iostream>
#include <cmath>
#include <fstream>
#include "Bod2D.h"


int compareFromHighest(const void * a1, const void * a2);

int main() {
    std::ofstream fout;
    std::ifstream fin;
    Line * arr = new Line[100];

    Line::getDistanceFromFile(fin,"usecky.txt", arr);
    Line::getSortedDistance(fout,"zoradeneUsecky.txt", arr, 100);

    delete [] arr;
    arr = NULL;


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


double Bod2D::distance(const Bod2D &point1 ) const
{
    Bod2D differenceP(x > 0 ? x-point1.x : point1.x-x, y >0 ? y-point1.y : point1.y-y);
    return sqrt(differenceP.x*differenceP.x + differenceP.y*differenceP.y);
}


Bod2D Bod2D::centerOfLine( const Bod2D & point1) const
{

    return { x+point1.x,y+point1.y};

}

void Bod2D::OpenFileCheck::getMsg() const
{
    std::cout<<msg;
}

int compareFromHighest(const void * a1, const void * a2)
{
    Line * p1 = (Line *)a1;
    Line * p2 = (Line *)a2;
    int result = 0;
    if((*p1)<(*p2))
    {
        result = 1;
    }
    if(!((*p1)<(*p2)))
    {
        result= -1;
    }
    return result;
}

void Line::getDistanceFromFile(std::ifstream & fin, const char * fileName,  Line arr[] )
{
    try {
        fin.open(fileName);
        if (!fin.is_open()) {
            throw Bod2D::OpenFileCheck("Something went wrong");
        };
        Bod2D A(0.0f,0);
        Bod2D B(0.0f,0);
        Bod2D Temp1(0.0f,0);
        Bod2D Temp2(0.0f,0);
        int i =0;

        double minDistance = Temp1.distance(Temp2);
        while (fin >> A >> B)
        {
            Line line(A,B);
            double currentDistance = A.distance(B);
            *(arr + i) = line;
            i++;
            if(minDistance<currentDistance)
            {
                Temp1 = A;
                Temp2 = B;
                minDistance = currentDistance;
            }
        }
        std::cout<< "Najmvacsia vzdialenost je medzi bodmi " << Temp1 << " a " << Temp2 << ", ma hodnotu: " << minDistance <<std::endl;
        fin.close();
    }
    catch (Bod2D::OpenFileCheck &ex)
    {
        ex.getMsg();
    }


}

void Line::getSortedDistance(std::ofstream & fout, const char * fileName, Line arr[], int numberOfElements)
{
    try
    {
        fout.open(fileName);
        if (!fout.is_open())
        {
            throw Bod2D::OpenFileCheck("Something went wrong");
        };
        qsort(arr,numberOfElements,sizeof(Line),compareFromHighest);//params: value, numberOfValues, sizeOf(type of the value), compareFunction;
        for(int i=0;i<numberOfElements;i++)
        {
            fout << *(arr + i)<< " Length: "<< (arr +i)->length << std::endl;
        }

        fout.close();
    }
    catch (Bod2D::OpenFileCheck &ex)
    {
        ex.getMsg();
    };
}

//DEKLARATION OF CHILD CLASS 'LINE'


Line::Line( Bod2D myBasePoint,  Bod2D myEndPoint): basePoint(myBasePoint), endPoint(myEndPoint){}

std::ostream & operator<<(std::ostream & os, const Line & line)
{
    os << line.basePoint << " " << line.endPoint;
    return os;
}

std::istream & operator>>(std::istream &is, Line & line)
{
    is >> line.basePoint >> line.endPoint;
    return is;
}

bool Line::operator<(Line & line1)
{
    return length<line1.length;
}







