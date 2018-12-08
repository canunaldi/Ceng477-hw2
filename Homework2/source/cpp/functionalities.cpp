#include "functionalities.h"
#include <cmath>

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

Matrix4x4 Matrix4x4::matrixCreator4x1(double m1,double m2,double m3,double m4){
    Matrix4x4 result;
    result.type = 2;
    result.matrix4x1[0] = m1;
    result.matrix4x1[1] = m2;
    result.matrix4x1[2] = m3;
    result.matrix4x1[3] = m4;
    return result;

}
double calculate_mult(double row, double column){
    return row * column;
}


Matrix4x4 Matrix4x4::operator*(Matrix4x4 right){
    Matrix4x4 result_matrix;
    if(this->type == 0 && right.type == 0){
        for (int i = 0; i<4 ; i++){
            for(int j = 0; j<4; j++){
                double sum = 0;
                for(int k = 0; k<4; k++)
                    sum += calculate_mult(this->matrix[i][k],right.matrix[k][j]);
                result_matrix.matrix[i][j] = sum;
            }
        }
        result_matrix.type = 0;
    }
    else if(this->type == 0 && right.type == 2){
        for (int i = 0; i < 4; i++) {
            double total = 0;
            for (int j = 0; j < 4; j++)
                total += this->matrix[i][j] * right.matrix4x1[j];
            result_matrix.matrix4x1[i] = total;
        }
        result_matrix.type = 2;
    }
    else if(this->type == 1 && right.type == 2){
        for (int i = 0; i < 3; i++) {
            double total = 0;
            for (int j = 0; j < 4; j++){
                total += this->matrix4x3[i][j] * right.matrix4x1[j];}
            result_matrix.matrix4x1[i] = total;
        }
        result_matrix.matrix4x1[3] = 0;
        result_matrix.type = 2;
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
    else if(result.type == 2){
        for(int i =0; i<4 ; i++){
            os<<"|";
            os<<result.matrix4x1[i];
            os<<"|\n";
        }
        os<<"__________";
        os<<"\n";
        

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


//GOKNUR


Matrix4x4 Matrix4x4::translationMatrix(Translation translate){

	 Matrix4x4 matrixT;
     matrixT.type=0;

	matrixT.matrix[0][0]= 1;
	matrixT.matrix[0][1]= 0;
	matrixT.matrix[0][2]= 0;
	matrixT.matrix[0][3]= translate.tx;

	matrixT.matrix[1][0]= 0;
	matrixT.matrix[1][1]= 1;
	matrixT.matrix[1][2]= 0;
	matrixT.matrix[1][3]= translate.ty;

	matrixT.matrix[2][0]= 0;
	matrixT.matrix[2][1]= 0;
	matrixT.matrix[2][2]= 1;
	matrixT.matrix[2][3]= translate.tz;

	matrixT.matrix[3][0]= 0;
	matrixT.matrix[3][1]= 0;
	matrixT.matrix[3][2]= 0;
	matrixT.matrix[3][3]= 1;

	return matrixT;
}


Matrix4x4 Matrix4x4::rotationMatrixM(Rotation rotate){

	Matrix4x4 matrixM;
    matrixM.type = 0;

	if((abs(rotate.uz) <= abs(rotate.ux)) && (abs(rotate.uz) <= abs(rotate.uy)))
	{
		matrixM.matrix[0][0]= rotate.ux;
		matrixM.matrix[0][1]= rotate.uy;
		matrixM.matrix[0][2]= rotate.uz;
		matrixM.matrix[0][3]= 0;

		matrixM.matrix[1][0]= -rotate.uy;
		matrixM.matrix[1][1]= rotate.ux;
		matrixM.matrix[1][2]= 0;
		matrixM.matrix[1][3]= 0;

		matrixM.matrix[2][0]= -rotate.uz*rotate.ux;
		matrixM.matrix[2][1]= -rotate.uz*rotate.uy;
		matrixM.matrix[2][2]= rotate.ux*rotate.ux + rotate.uy*rotate.uy;
		matrixM.matrix[2][3]= 0;

		matrixM.matrix[3][0]= 0;
		matrixM.matrix[3][1]= 0;
		matrixM.matrix[3][2]= 0;
		matrixM.matrix[3][3]= 1;
}

	else if((abs(rotate.uy) <= abs(rotate.ux)) && (abs(rotate.uy) <= abs(rotate.uz)))
	{
		matrixM.matrix[0][0]= rotate.ux;
		matrixM.matrix[0][1]= rotate.uy;
		matrixM.matrix[0][2]= rotate.uz;
		matrixM.matrix[0][3]= 0;

		matrixM.matrix[1][0]= -rotate.uz;
		matrixM.matrix[1][1]= 0;
		matrixM.matrix[1][2]= rotate.ux;
		matrixM.matrix[1][3]= 0;

		matrixM.matrix[2][0]= rotate.uy*rotate.ux;
		matrixM.matrix[2][1]= -rotate.ux*rotate.ux-rotate.uz*rotate.uz;
		matrixM.matrix[2][2]= rotate.uy*rotate.uz;
		matrixM.matrix[2][3]= 0;

		matrixM.matrix[3][0]= 0;
		matrixM.matrix[3][1]= 0;
		matrixM.matrix[3][2]= 0;
		matrixM.matrix[3][3]= 1;		
	}

	else{
		matrixM.matrix[0][0]= rotate.ux;
		matrixM.matrix[0][1]= rotate.uy;
		matrixM.matrix[0][2]= rotate.uz;
		matrixM.matrix[0][3]= 0;

		matrixM.matrix[1][0]= 0;
		matrixM.matrix[1][1]= -rotate.uz;
		matrixM.matrix[1][2]= rotate.uy;
		matrixM.matrix[1][3]= 0;

		matrixM.matrix[2][0]= rotate.uy*rotate.uy + rotate.uz*rotate.uz;
		matrixM.matrix[2][1]= -rotate.ux*rotate.uy;
		matrixM.matrix[2][2]= -rotate.ux*rotate.uz;
		matrixM.matrix[2][3]= 0;

		matrixM.matrix[3][0]= 0;
		matrixM.matrix[3][1]= 0;
		matrixM.matrix[3][2]= 0;
		matrixM.matrix[3][3]= 1;		
	}

	return matrixM;
}

Matrix4x4 Matrix4x4::rotationMatrixminusM(Rotation rotate){
	Matrix4x4 matrixMinusM;
    matrixMinusM.type =0;

	if((abs(rotate.uz) <= abs(rotate.ux)) && (abs(rotate.uz) <= abs(rotate.uy))){
		matrixMinusM.matrix[0][0]= rotate.ux;
		matrixMinusM.matrix[0][1]= -rotate.uy;
		matrixMinusM.matrix[0][2]= -rotate.uz*rotate.ux;
		matrixMinusM.matrix[0][3]= 0;

		matrixMinusM.matrix[1][0]= rotate.uy;
		matrixMinusM.matrix[1][1]= rotate.ux;
		matrixMinusM.matrix[1][2]= -rotate.uz*rotate.uy;
		matrixMinusM.matrix[1][3]= 0;

		matrixMinusM.matrix[2][0]= rotate.uz;
		matrixMinusM.matrix[2][1]= 0;
		matrixMinusM.matrix[2][2]= rotate.ux*rotate.ux + rotate.uy*rotate.uy;
		matrixMinusM.matrix[2][3]= 0;

		matrixMinusM.matrix[3][0]= 0;
		matrixMinusM.matrix[3][1]= 0;
		matrixMinusM.matrix[3][2]= 0;
		matrixMinusM.matrix[3][3]= 1;
}

	else if((abs(rotate.uy) <= abs(rotate.ux)) && (abs(rotate.uy) <= abs(rotate.uz)))
	{
		matrixMinusM.matrix[0][0]= rotate.ux;
		matrixMinusM.matrix[0][1]= -rotate.uz;
		matrixMinusM.matrix[0][2]= rotate.uy*rotate.ux;
		matrixMinusM.matrix[0][3]= 0;

		matrixMinusM.matrix[1][0]= rotate.uy;
		matrixMinusM.matrix[1][1]= 0;
		matrixMinusM.matrix[1][2]= -rotate.ux*rotate.ux-rotate.uz*rotate.uz;
		matrixMinusM.matrix[1][3]= 0;

		matrixMinusM.matrix[2][0]= rotate.uz;
		matrixMinusM.matrix[2][1]= rotate.ux;
		matrixMinusM.matrix[2][2]= rotate.uy*rotate.uz;
		matrixMinusM.matrix[2][3]= 0;

		matrixMinusM.matrix[3][0]= 0;
		matrixMinusM.matrix[3][1]= 0;
		matrixMinusM.matrix[3][2]= 0;
		matrixMinusM.matrix[3][3]= 1;		
	}

	else{
		matrixMinusM.matrix[0][0]= rotate.ux;
		matrixMinusM.matrix[0][1]= 0;
		matrixMinusM.matrix[0][2]= rotate.uy*rotate.uy + rotate.uz*rotate.uz;
		matrixMinusM.matrix[0][3]= 0;

		matrixMinusM.matrix[1][0]= rotate.uy;
		matrixMinusM.matrix[1][1]= -rotate.uz;
		matrixMinusM.matrix[1][2]= -rotate.ux*rotate.uy;
		matrixMinusM.matrix[1][3]= 0;

		matrixMinusM.matrix[2][0]= rotate.uz;
		matrixMinusM.matrix[2][1]= rotate.uy;
		matrixMinusM.matrix[2][2]= -rotate.ux*rotate.uz;
		matrixMinusM.matrix[2][3]= 0;

		matrixMinusM.matrix[3][0]= 0;
		matrixMinusM.matrix[3][1]= 0;
		matrixMinusM.matrix[3][2]= 0;
		matrixMinusM.matrix[3][3]= 1;		
	}
	return matrixMinusM;
}


Matrix4x4 Matrix4x4::rotationMatrix(Rotation rotate){

	Matrix4x4 matrixRx;
    matrixRx.type=0;

	matrixRx.matrix[0][0]= 1;
	matrixRx.matrix[0][1]= 0;
	matrixRx.matrix[0][2]= 0;
	matrixRx.matrix[0][3]= 0;

	matrixRx.matrix[1][0]= 0;
	matrixRx.matrix[1][1]= cos(rotate.angle * M_PI / 180) ;
	matrixRx.matrix[1][2]= -sin(rotate.angle * M_PI / 180);
	matrixRx.matrix[1][3]= 0;

	matrixRx.matrix[2][0]= 0;
	matrixRx.matrix[2][1]= sin(rotate.angle * M_PI / 180);
	matrixRx.matrix[2][2]= cos(rotate.angle * M_PI / 180);
	matrixRx.matrix[2][3]= 0;

	matrixRx.matrix[3][0]= 0;
	matrixRx.matrix[3][1]= 0;
	matrixRx.matrix[3][2]= 0;
	matrixRx.matrix[3][3]= 1;

	return matrixRx;
}


Matrix4x4 Matrix4x4::ScalingMatrix(Scaling scale){

	Matrix4x4 matrixS;
    matrixS.type=0;

	matrixS.matrix[0][0]= scale.sx;
	matrixS.matrix[0][1]= 0;
	matrixS.matrix[0][2]= 0;
	matrixS.matrix[0][3]= 0;

	matrixS.matrix[1][0]= 0;
	matrixS.matrix[1][1]= scale.sy;
	matrixS.matrix[1][2]= 0;
	matrixS.matrix[1][3]= 0;
	
	matrixS.matrix[2][0]= 0;
	matrixS.matrix[2][1]= 0;
	matrixS.matrix[2][2]= scale.sz;
	matrixS.matrix[2][3]= 0;
	
	matrixS.matrix[3][0]= 0;
	matrixS.matrix[3][1]= 0;
	matrixS.matrix[3][2]= 0;
	matrixS.matrix[3][3]= 1;

	return matrixS;
}


