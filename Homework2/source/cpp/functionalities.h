#include <iostream>
#include "hw2_types.h"
using namespace std;




struct Matrix4x4{
    double matrix[4][4];
    double matrix4x3[3][4];
    int type;
    Matrix4x4 operator*(Matrix4x4 right);
    Matrix4x4 matrixCreator(double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double);
    Matrix4x4 matrixCreator4x3(double,double,double,double,double,double,double,double,double,double,double,double);
    friend ostream& operator<<(ostream& os, Matrix4x4& element);
};




