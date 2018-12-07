#include "functionalities.h"

Matrix4x4 Matrix4x4::matrixCreator(double m1,double m2,double m3,double m4,double m5,double m6,double m7,double m8,double m9,double m10,double m11,double m12,double m13,double m14,double m15,double m16){
    Matrix4x4 result;
    result.matrix[0][0] = m1;
    result.matrix[0][1] = m2;
    result.matrix[0][2] = m3;
    result.matrix[0][3] = m4;
    result.matrix[1][0] = m5;
    result.matrix[1][1] = m6;
    result.matrix[1][2] = m7;
    result.matrix[1][3] = m8;
    result.matrix[2][0] = m9;
    result.matrix[2][1] = m10;
    result.matrix[2][2] = m11;
    result.matrix[2][3] = m12;
    result.matrix[3][0] = m13;
    result.matrix[3][1] = m14;
    result.matrix[3][2] = m15;
    result.matrix[3][3] = m16;
    return result;

}
double calculate_mult(double row[4], double column[4]){
    return row[0]*column[0] + row[1]*column[1] + row[2]*column[2] + row[3]*column[3];
}


ostream& operator<<(ostream& os, Matrix4x4& result){
    os<<"\n";
    for (int i = 0; i<4 ; i++){
        os<<"| ";
        for(int j = 0; j<4; j++){
            os<<result.matrix[i][j];
            os<<" ";
        }
        os<<"|\n";
    }
    return os;
    
}


