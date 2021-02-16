#ifndef BOD_BOD2D_CPP
#define BOD_BOD2D_CPP

#include "Bod2D.h"
#include "inout.h"
#include <cmath>


using namespace inout;

Bod2D::Bod2D()
{
    std::cout<<"Zadaj suradnicu 'x' a 'y': " << std::endl;
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

Vektor Line::getNormalovy() const
{
    Bod2D tmp = basePoint-endPoint;
    return{-tmp.getX(),tmp.getY()};
}
Vektor Line::getSmerovy() const
{
    Bod2D tmp = basePoint-endPoint;
    return{tmp.getX(),tmp.getY()};
}
Bod2D Line::getCenter() const
{
    return{basePoint-endPoint};
}

Line::VR Line::generalFormula() const
{
    std::cout<< inout::showpos << " Usecka sa sklada z bodov " << basePoint << " a " << endPoint << std::endl;
    float a = this->getNormalovy().getX();
    float b = this->getNormalovy().getY();
    float c = -a*basePoint.getX()-b*basePoint.getY();
    Line::VR gF(a,b,c);
    std::cout<< gF << std::endl;
    return gF;
}

Line::PR Line::directionFormula() const
{
    float a1 = basePoint.getX();
    float v1 = this->getSmerovy().getX();
    float a2 = basePoint.getY();
    float v2 = this->getSmerovy().getY();
    Line::PR dF(a1,v1,a2,v2);
    std::cout <<  dF << std::endl;
    return dF;
}

Line::operator Line::VR() const
{
    return this->generalFormula();
}

Line::operator Line::PR() const
{
    return this->directionFormula();
}

Line::VR Line::lineAxis() const
{
    Bod2D center = this->getCenter();
    Bod2D otherPoint = center + this->getNormalovy();
    Line axis(center, otherPoint);
    return axis.generalFormula();
}

bool Line::areParallel(Line line) const {

    Vektor s1 = this->getSmerovy();
    Vektor s2 = line.getSmerovy();

    return (s1.getX()/s2.getX() == s1.getY()/s2.getY());


};

//definicie VR
std::ostream & operator<<(std::ostream & os, Line::VR & vr)
{
    os << inout::showpos<< " "<< vr.coef[0] << "x" << " " << vr.coef[1] << "y" << " "<<  vr.coef[2] << " = 0";
    return os;

}

//definice PR
std::ostream & operator<<(std::ostream & os, Line::PR & pr)
{
    os << inout::showpos<< "x = " << pr.paramCoef[0] << pr.paramCoef[1] << "t" <<std::endl;
    os << inout::showpos<< "y = " << pr.paramCoef[2] << pr.paramCoef[3] << "t" << " , t is member of Z"<<std::endl;
    return os;
}

std::istream & operator>>(std::istream & is, Line::PR & pr)
{
    for(int i=0; i<4; ++i)
    {
        is >> pr.paramCoef[i];
    }
    return is;
}



#endif