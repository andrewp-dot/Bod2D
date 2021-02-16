#include <iostream>
#include <fstream>
#include "Bod2D.h"
#include "Bod2D.cpp"


int compareFromHighest(const void * a1, const void * a2);

int main() {
    std::ofstream fout;
    std::ifstream fin;
    Line * arr = new Line[100];

    Line::getDistanceFromFile(fin,"usecky.txt", arr);
    Line::getSortedDistance(fout,"zoradeneUsecky.txt", arr, 100);


    Bod2D a(1.0f,3);
    Bod2D b(3.0f,7);
    Line line(a,b);
    std::cout << "Line axis: ", line.lineAxis();
    (Line::VR)(line); //pretypovanie
    (Line::PR)(line);
    line.generalFormula(); //volanim funkcie
    line.directionFormula();

    delete [] arr;
    arr = NULL;


    return 0;
}






