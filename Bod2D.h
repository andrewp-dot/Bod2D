#ifndef BOD_BOD2D_H
#define BOD_BOD2D_H


class Bod2D {
private:
    float x;
    float y;
public:

    Bod2D();
    Bod2D(char coordinatesType, float myCoordinates);
    Bod2D(float myX, float myY):x(myX),y(myY) {};

    float getX() const {return x;} ;
    float getY() const {return y;} ;
    void setX(float valX){x=valX;};
    void setY(float valY){y=valY;};

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
        explicit OpenFileCheck(const char * currentMsg):msg(currentMsg){};
        void getMsg() const;
    };

};

using Vektor = Bod2D;


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

    Vektor getNormalovy() const;
    Vektor getSmerovy() const;
    Bod2D getCenter() const;



    //musi byt public
    class VR
    {
    private:
        float coef[3];
    public:
        VR(float ka,float kb, float kc):coef{ka,kb,kc}{};
        friend std::ostream & operator<<(std::ostream & os, VR & vr);
        float & operator[](int index) {return coef[index];};
        const float & operator[](int index) const {return coef[index];};

    };

    class PR
    {
    private:
        float paramCoef[4];
    public:
        PR(float ka1,float kv1, float ka2,float kv2):paramCoef{ka1,kv1,ka2,kv2}{};
        friend std::ostream & operator<<(std::ostream & os, PR & pr);
        friend std::istream & operator>>(std::istream & is, Line::PR & pr);

    };

    explicit operator VR() const;
    explicit operator PR() const;

    VR generalFormula() const;
    PR directionFormula() const;
    VR lineAxis() const; //os úsečky
    bool areParallel(Line line) const;

};


#endif //BOD_BOD2D_H
