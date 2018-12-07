#include "functionalities.h"

Matrix4x4 Matrix4x4::matrixCreator(double m1,double m2,double m3,double m4,double m5,double m6,double m7,double m8,double m9,double m10,double m11,double m12,double m13,double m14,double m15,double m16){
    Matrix4x4 result;
    result.type = 0;
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


Matrix4x4 Matrix4x4::matrixCreator4x3(double m1,double m2,double m3,double m4,double m5,double m6,double m7,double m8,double m9,double m10,double m11,double m12){
    Matrix4x4 result;
    result.type = 1;
    result.matrix4x3[0][0] = m1;
    result.matrix4x3[0][1] = m2;
    result.matrix4x3[0][2] = m3;
    result.matrix4x3[0][3] = m4;
    result.matrix4x3[1][0] = m5;
    result.matrix4x3[1][1] = m6;
    result.matrix4x3[1][2] = m7;
    result.matrix4x3[1][3] = m8;
    result.matrix4x3[2][0] = m9;
    result.matrix4x3[2][1] = m10;
    result.matrix4x3[2][2] = m11;
    result.matrix4x3[2][3] = m12;
    return result;

}
double calculate_mult(double row, double column){
    return row * column;
}


Matrix4x4 Matrix4x4::operator*(Matrix4x4 right){
    Matrix4x4 result_matrix;
    result_matrix.type = 0;
    for (int i = 0; i<4 ; i++){
        for(int j = 0; j<4; j++){
            double sum = 0;
            for(int k = 0; k<4; k++)
                sum += calculate_mult(this->matrix[i][k],right.matrix[k][j]);
            result_matrix.matrix[i][j] = sum;
        }
    }
    return result_matrix;

}

ostream& operator<<(ostream& os, Matrix4x4& result){
    os<<"\n";
    if(result.type == 0){
        for (int i = 0; i<4 ; i++){
        os<<"| ";
        for(int j = 0; j<4; j++){
            os<<result.matrix[i][j];
            os<<" ";
        }
        os<<"|\n";
        }
    }
    else{
        for (int i = 0; i<3 ; i++){
        os<<"| ";
        for(int j = 0; j<4; j++){
            os<<result.matrix4x3[i][j];
            os<<" ";
        }
        os<<"|\n";

    }

    }
    
    return os;
    
}


