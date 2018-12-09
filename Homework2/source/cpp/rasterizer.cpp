#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "hw2_types.h"
#include "hw2_math_ops.h"
#include "hw2_file_ops.h"
#include <iostream>

using namespace std;

Camera cameras[100];
int numberOfCameras = 0;

Model models[1000];
int numberOfModels = 0;

Color colors[100000];
int numberOfColors = 0;

Translation translations[1000];
int numberOfTranslations = 0;

Rotation rotations[1000];
int numberOfRotations = 0;

Scaling scalings[1000];
int numberOfScalings = 0;

Vec3 vertices[100000];
int numberOfVertices = 0;

Color backgroundColor;

// backface culling setting, default disabled
int backfaceCullingSetting = 0;

Color **image;


//FUNCTIONALITIES//


struct Matrix4x4{
    double matrix[4][4];
    double matrix4x3[3][4];
    double matrix4x1[4];
    int type;
    Matrix4x4 operator*(Matrix4x4 right);
    Matrix4x4 operator-(Matrix4x4 right);
    Matrix4x4 matrixCreator(double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double);
    Matrix4x4 matrixCreator4x3(double,double,double,double,double,double,double,double,double,double,double,double);
    Matrix4x4 matrixCreator4x1(double,double,double,double);
    Matrix4x4 translationMatrix(Translation translate);
    Matrix4x4 rotationMatrixM(Rotation rotate);
    Matrix4x4 rotationMatrixminusM(Rotation rotate);
    Matrix4x4 rotationMatrix(Rotation rotate);
    Matrix4x4 ScalingMatrix(Scaling scale);
    friend ostream& operator<<(ostream& os, Matrix4x4& element);
};




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


Matrix4x4 Matrix4x4::operator-(Matrix4x4 right){
    Matrix4x4 resultmatrix;
    resultmatrix.matrix4x1[0] = right.matrix4x1[0] - (this->matrix4x1[0]);
    resultmatrix.matrix4x1[1] = right.matrix4x1[1] - this->matrix4x1[1];
    resultmatrix.matrix4x1[2] = right.matrix4x1[2] - this->matrix4x1[2];
    return resultmatrix;

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
    Vec3 rotate2;
    rotate2.x = rotate.ux;
    rotate2.y = rotate.uy;
    rotate2.z = rotate.uz;
    normalizeVec3(rotate2);
    rotate.ux = rotate2.x;
    rotate.uy = rotate2.y;
    rotate.uz = rotate2.z;

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
    Vec3 rotate2;
    rotate2.x = rotate.ux;
    rotate2.y = rotate.uy;
    rotate2.z = rotate.uz;
    normalizeVec3(rotate2);
    rotate.ux = rotate2.x;
    rotate.uy = rotate2.y;
    rotate.uz = rotate2.z;
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
	matrixRx.matrix[1][1]= cos(rotate.angle * M_PI / 180.0) ;
	matrixRx.matrix[1][2]= -sin(rotate.angle * M_PI / 180.0);
	matrixRx.matrix[1][3]= 0;

	matrixRx.matrix[2][0]= 0;
	matrixRx.matrix[2][1]= sin(rotate.angle * M_PI / 180.0);
	matrixRx.matrix[2][2]= cos(rotate.angle * M_PI / 180.0);
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




//--------------//

/*
    Initializes image with background color
*/
void initializeImage(Camera cam) {
    int i, j;

    for (i = 0; i < cam.sizeX; i++)
        for (j = 0; j < cam.sizeY; j++) {
            image[i][j].r = backgroundColor.r;
            image[i][j].g = backgroundColor.g;
            image[i][j].b = backgroundColor.b;

        }
}

/*
    Transformations, culling, rasterization are done here.
    You can define helper functions inside this file (rasterizer.cpp) only.
    Using types in "hw2_types.h" and functions in "hw2_math_ops.cpp" will speed you up while working.
*/

Matrix4x4 calculatecamTransform(Camera cam){
    Matrix4x4 first;
    Matrix4x4 second;
    first = first.matrixCreator(cam.u.x,cam.u.y,cam.u.z,0,cam.v.x,cam.v.y,cam.v.z,0,cam.w.x,cam.w.y,cam.w.z,0,0,0,0,1);
    second = second.matrixCreator(1,0,0,-cam.pos.x,0,1,0,-cam.pos.y,0,0,1,-cam.pos.z,0,0,0,1);
    Matrix4x4 deneme = first*second;
    deneme.type = 0;

    return first*second;
}

Matrix4x4 calculatePersTransform(Camera cam){
    double r11 = (2*cam.n)/(cam.r-cam.l);
    double r13 = (cam.r + cam.l)/(cam.r - cam.l);
    double r22 = (2*cam.n)/(cam.t-cam.b);
    double r23 = (cam.t + cam.b)/(cam.t - cam.b);
    double r33 = -(cam.f+cam.n)/(cam.f-cam.n);
    double r34 = -(cam.f*cam.n)/(cam.f-cam.n);
    double r43 = -1;
    Matrix4x4 perspective = perspective.matrixCreator(r11,0,r13,0,0,r22,r23,0,0,0,r33,r34,0,0,r43,0);
    return perspective;

}

Matrix4x4 calculateViewPort(Camera cam){
    double r11 = cam.sizeX/2.0;
    double r14 = (cam.sizeX -1)/2.0;
    double r22 = cam.sizeY/2.0;
    double r24 = (cam.sizeY-1)/2.0;
    double r33 = 1.0/2.0;
    double r34 = 1.0/2.0;
    Matrix4x4 viewPort = viewPort.matrixCreator4x3(r11,0,0,r14,0,r22,0,r24,0,0,r33,r34);
    return viewPort;

}

Color color_decider(Vec3 v1,Vec3 v2){
    return colors[v1.colorId];
}

void slope_decider(int& x0, int& y0, int& x1, int& y1, int& type, int& slope){
    double currs = double( abs(y1-y0) )/ double( abs(x1-x0));
    if(currs > 1){
        slope = 1;
    }
    else{
        slope = 0;
    }
    if(x1>=x0 && y1>=y0) {type = 0;}
    else if(x0>=x1 && y1>=y0) type = 1;
    else if(x1>=x0 && y0>=y1) type = 2;
    else if(x0>=x1 && y0>=y1) type = 3;
    else type =4;
}

void rasterize(Vec3 v1, Vec3 v2){
    int type= 0;
    int x0 = v1.x;
    int y0 = v1.y;
    Color color0 = colors[v1.colorId];
    int x1 = v2.x;
    int y1 = v2.y;
    Color color1 = colors[v2.colorId];
    int slope = 0;
    int slope2 = 0;
    slope_decider(x0,y0,x1,y1,type,slope2);
    if(type == 0){

    }
    else if(type == 1){
        x0 = v2.x;
        y0 = v2.y;
        color0 = colors[v2.colorId];
        x1 = v1.x;
        y1 = v1.y;
        color1 = colors[v1.colorId];
        slope = 1;
         //cout<<"DOGRU BILDIN"<<endl;
    }
    else if(type == 2){
        slope = 1;
    }
    else if(type == 3){
        x0 = v2.x;
        y0 = v2.y;
        color0 = colors[v2.colorId];
        x1 = v1.x;
        y1 = v1.y;
        color1 = colors[v1.colorId];
       
    }
    else{
        cout<<"ERROR at X: "<<x0<<", Y: "<<y0<<", X1: "<<x1<<", Y1: "<<y1<<endl;
    }
    if (slope == 0){
        if(slope2 == 0){
            int y = y0;
            int d = 2*(y0 - y1) + (x1-x0);
            for(int x =x0; x<x1; x++){
                //cout<<"X: "<<x<<" Y: "<<y<<endl;
                //cout<<"ILK X: "<<x<<", "<<y<<endl;
                  Color color;
                   if(x1==x0){
                color.r = (color0.r*(y1-y)+color1.r*(y-y0))/(y1-y0);
                color.g = (color0.g*(y1-y)+color1.g*(y-y0))/(y1-y0);
                color.b = (color0.b*(y1-y)+color1.b*(y-y0))/(y1-y0);
                }
                else{
                color.r = (color0.r*(x1-x)+color1.r*(x-x0))/(x1-x0);
                color.g = (color0.g*(x1-x)+color1.g*(x-x0))/(x1-x0);
                color.b = (color0.b*(x1-x)+color1.b*(x-x0))/(x1-x0);
            }
                image[x][y].r = color.r;
                image[x][y].g = color.g;
                image[x][y].b = color.b;
                if(d<0){
                    y+=1;
                    d+= 2*((y0 -y1) + (x1-x0)); 
                    
                }
                else{
                    d+= 2*(y0-y1);
                }
            }

        }
        else{
            int x = x0;
            int d = 2*(x0 - x1) + (y1-y0);
           // cout<<"GIRIS"<<endl;
           // cout<<"X0: "<<x0<<", Y0:"<<y0<<", X1:"<<x1<<", Y1:"<<y1<<endl;
           // cout<<"Type: "<<type<<endl;
            for(int y =y0; y<y1; y++){
                //cout<<"X: "<<x<<" Y: "<<y<<endl;
                //cout<<"ILK X: "<<x<<", "<<y<<endl;
                Color color;
                
                if(d<0){
                    color.r = (color0.r*(x1-x)+color1.r*(x-x0))/(x1-x0);
                    color.g = (color0.g*(x1-x)+color1.g*(x-x0))/(x1-x0);
                    color.b = (color0.b*(x1-x)+color1.b*(x-x0))/(x1-x0);
                    image[x][y].r = color.r;
                    image[x][y].g = color.g;
                    image[x][y].b = color.b;
                    x+=1;
                    d+= 2*((x0 -x1) + (y1-y0)); 
                    
                }
                else{
                    color.r = (color0.r*(y1-y)+color1.r*(y-y0))/(y1-y0);
                    color.g = (color0.g*(y1-y)+color1.g*(y-y0))/(y1-y0);
                    color.b = (color0.b*(y1-y)+color1.b*(y-y0))/(y1-y0);
                    image[x][y].r = color.r;
                    image[x][y].g = color.g;
                    image[x][y].b = color.b;
                    d+= 2*(x0-x1);
                }
            }
            //cout<<"CIKIS"<<endl;


        }
        
    }
    else{
        if(slope2 == 0){
            int y = y0;
            int d = 2*((y1) - (y0)) + (x1-x0);
            for(int x =x0; x<x1; x++){
                //cout<<"X: "<<x<<" Y: "<<y<<endl;
                //cout<<"ILK X: "<<x<<", "<<y<<endl;
                Color color;
                 if(x1==x0){
                color.r = (color0.r*(y1-y)+color1.r*(y-y0))/(y1-y0);
                color.g = (color0.g*(y1-y)+color1.g*(y-y0))/(y1-y0);
                color.b = (color0.b*(y1-y)+color1.b*(y-y0))/(y1-y0);
                }
                else{
                color.r = (color0.r*(x1-x)+color1.r*(x-x0))/(x1-x0);
                color.g = (color0.g*(x1-x)+color1.g*(x-x0))/(x1-x0);
                color.b = (color0.b*(x1-x)+color1.b*(x-x0))/(x1-x0);
            }
                image[x][y].r = color.r;
                image[x][y].g = color.g;
                image[x][y].b = color.b;
                if(d<0){
                    y-=1;
                    d+= 2*(((y1) -(y0)) + (x1-x0)); 
                    
                }
                else{
                    d+= 2*((y1)-(y0));
                }
            }

        }
        else{
            int x = x0;
            int d = 2*(x0 - x1) + ((y0)-(y1));
            //cout<<"GIRIS"<<endl;
            //cout<<"X0: "<<x0<<", Y0:"<<y0<<", X1:"<<x1<<", Y1:"<<y1<<endl;
            //cout<<"Type: "<<type<<endl;
            for(int y =y0; y>y1; y--){
                //cout<<"X: "<<x<<" Y: "<<y<<endl;
                //cout<<"IKI X: "<<x<<", "<<y<<endl;
                Color color;
             
                
                if(d<0){
                    color.r = (color0.r*(x1-x)+color1.r*(x-x0))/(x1-x0);
                    color.g = (color0.g*(x1-x)+color1.g*(x-x0))/(x1-x0);
                    color.b = (color0.b*(x1-x)+color1.b*(x-x0))/(x1-x0);
                    image[x][y].r = color.r;
                    image[x][y].g = color.g;
                    image[x][y].b = color.b;
                    x+=1;
                    d+= 2*((x0 -x1) + ((y0)-(y1))); 
                    
                }
                else{
                    color.r = (color0.r*(y1-y)+color1.r*(y-y0))/(y1-y0);
                    color.g = (color0.g*(y1-y)+color1.g*(y-y0))/(y1-y0);
                    color.b = (color0.b*(y1-y)+color1.b*(y-y0))/(y1-y0);
                    image[x][y].r = color.r;
                    image[x][y].g = color.g;
                    image[x][y].b = color.b;
                    d+= 2*(x0-x1);
                }
            }
            //cout<<"CIKIS"<<endl;


        }

    }
   
}

double f_Equalities(int x0,int x1,int y0,int y1, int x, int y){
    return x*(y0-y1) + y*(x1-x0) + x0*y1 - y0*x1;

}

void rasterizeTriangle(Vec3 v1, Vec3 v2,  Vec3 v3){
    int x0 = v1.x, x1 = v2.x, x2 = v3.x;
    int y0 = v1.y, y1 = v2.y, y2 = v3.y;
    int xmin = min(x0,min(x1,x2));
    int ymin = min(y0,min(y1,y2));
    int xmax = max(x0,max(x1,x2));
    int ymax = max(y0,max(y1,y2));
    int x,y;
    Color color0 = colors[v1.colorId];
    Color color1 = colors[v2.colorId];
    Color color2 = colors[v3.colorId];
    Color color;
    double alpha,beta,gamma;
    for (y = ymin; y<ymax; y++){
        for(x = xmin; x<xmax; x++){
            alpha = f_Equalities(x1,x2,y1,y2,x,y)/f_Equalities(x1,x2,y1,y2,x0,y0);
            beta = f_Equalities(x2,x0,y2,y0,x,y)/f_Equalities(x2,x0,y2,y0,x1,y1);
            gamma = f_Equalities(x0,x1,y0,y1,x,y)/f_Equalities(x0,x1,y0,y1,x2,y2);
            if(alpha >= 0 && beta >= 0 && gamma >=0){
                color.r = round(alpha*color0.r + beta*color1.r + gamma*color2.r);
                color.g = round(alpha*color0.g + beta*color1.g + gamma*color2.g);
                color.b = round(alpha*color0.b + beta*color1.b + gamma*color2.b);
                image[x][y].r = color.r;
                image[x][y].g = color.g;
                image[x][y].b = color.b;
            }
        }
    }


}



void forwardRenderingPipeline(Camera cam) {

    Matrix4x4 camTransform = calculatecamTransform(cam);
    Matrix4x4 persTransform = calculatePersTransform(cam);
    Matrix4x4 viewportTransform = calculateViewPort(cam);
    
    for(int i = 0; i<numberOfModels; i++){
        int numberoftransform = models[i].numberOfTransformations;
        int numberofTriangles = models[i].numberOfTriangles;
        for(int j=0; j<numberofTriangles; j++){
            Triangle currentTriangle = models[i].triangles[j];
            Vec3 v1 = vertices[currentTriangle.vertexIds[0]];
            Vec3 v2 = vertices[currentTriangle.vertexIds[1]];
            Vec3 v3 = vertices[currentTriangle.vertexIds[2]];
            Matrix4x4 verticeMatrix = verticeMatrix.matrixCreator4x1(v1.x,v1.y,v1.z,1.0);
            Matrix4x4 verticeMatrix1 = verticeMatrix1.matrixCreator4x1(v2.x,v2.y,v2.z,1.0);
            Matrix4x4 verticeMatrix2 = verticeMatrix2.matrixCreator4x1(v3.x,v3.y,v3.z,1.0);
            Matrix4x4 totalTransform = totalTransform.matrixCreator(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
            totalTransform.type = 0;
            Matrix4x4 transform;
            transform.type = 0;
            
            for(int k=0; k<numberoftransform; k++){
                char currenttransform = models[i].transformationTypes[k];
                int currenttransformid = models[i].transformationIDs[k];

                
                if(k == 0){
                    if(currenttransform == 't'){
                        totalTransform = totalTransform.translationMatrix(translations[currenttransformid]);
                        //cout<<totalTransform<<endl;
                    }
                    else if(currenttransform == 's'){
                        totalTransform = totalTransform.ScalingMatrix(scalings[currenttransformid]);
                    }
                    else{
                        totalTransform = totalTransform.rotationMatrixM(rotations[currenttransformid]);
                        totalTransform = totalTransform.rotationMatrix(rotations[currenttransformid]) * totalTransform;
                        totalTransform = totalTransform.rotationMatrixminusM(rotations[currenttransformid]) * totalTransform;

                    }

                }
                if(currenttransform == 't'){
                    transform = transform.translationMatrix(translations[currenttransformid]);
                }
                else if(currenttransform == 's'){
                    transform = transform.ScalingMatrix(scalings[currenttransformid]);
                }
                else{
                    transform = transform.rotationMatrixM(rotations[currenttransformid]);
                    transform = transform.rotationMatrix(rotations[currenttransformid]) * transform;
                    transform = transform.rotationMatrixminusM(rotations[currenttransformid]) * transform;

                }
                if(k == 0){

                }
                else{
                    totalTransform = transform * totalTransform;
                }

                


                
            }
            
            //cout<<totalTransform<<endl;
            totalTransform = camTransform * totalTransform;
            
            //cout<<totalTransform<<endl;
            totalTransform = persTransform * totalTransform;
            
            //cout<<totalTransform<<endl;
            verticeMatrix = totalTransform * verticeMatrix;
            verticeMatrix1 = totalTransform * verticeMatrix1;
            verticeMatrix2 = totalTransform * verticeMatrix2;


            v1.x = verticeMatrix.matrix4x1[0]; v1.y = verticeMatrix.matrix4x1[1]; v1.z = verticeMatrix.matrix4x1[2];
            v2.x = verticeMatrix1.matrix4x1[0]; v2.y = verticeMatrix1.matrix4x1[1]; v2.z = verticeMatrix1.matrix4x1[2];
            v3.x = verticeMatrix2.matrix4x1[0]; v3.y = verticeMatrix2.matrix4x1[1]; v3.z = verticeMatrix2.matrix4x1[2];
            if(backfaceCullingSetting == 1){
                Vec3 v0v1, v0v2, normal,camtotriangle;
                double cullingdecide1,cullingdecide2,cullingdecide3;
                v0v1 = subtractVec3(v2,v1);
                v0v2 = subtractVec3(v3,v1);
                normal = crossProductVec3(v0v2,v0v1);
                camtotriangle = subtractVec3(v1,cam.pos);
                cullingdecide1 = dotProductVec3(normal,camtotriangle);
                camtotriangle = subtractVec3(v1,cam.pos);
                cullingdecide2 = dotProductVec3(normal,camtotriangle);
                camtotriangle = subtractVec3(v1,cam.pos);
                cullingdecide3 = dotProductVec3(normal,camtotriangle);

                if(cullingdecide1 > 0 || cullingdecide2 > 0 || cullingdecide3 > 0){
                    continue;
                }

            }
            verticeMatrix.matrix4x1[0] = verticeMatrix.matrix4x1[0]/verticeMatrix.matrix4x1[3];
            verticeMatrix.matrix4x1[1] = verticeMatrix.matrix4x1[1]/verticeMatrix.matrix4x1[3];
            verticeMatrix.matrix4x1[2] = verticeMatrix.matrix4x1[2]/verticeMatrix.matrix4x1[3];
            verticeMatrix.matrix4x1[3] = 1;
            
            

            
            verticeMatrix = viewportTransform * verticeMatrix;

            

            //cout<<verticeMatrix<<endl;
            verticeMatrix1.matrix4x1[0] = verticeMatrix1.matrix4x1[0]/verticeMatrix1.matrix4x1[3];
            verticeMatrix1.matrix4x1[1] = verticeMatrix1.matrix4x1[1]/verticeMatrix1.matrix4x1[3];
            verticeMatrix1.matrix4x1[2] = verticeMatrix1.matrix4x1[2]/verticeMatrix1.matrix4x1[3];
            verticeMatrix1.matrix4x1[3] = 1;
            verticeMatrix1 = viewportTransform * verticeMatrix1;
            //cout<<verticeMatrix1<<endl;
            verticeMatrix2.matrix4x1[0] = verticeMatrix2.matrix4x1[0]/verticeMatrix2.matrix4x1[3];
            verticeMatrix2.matrix4x1[1] = verticeMatrix2.matrix4x1[1]/verticeMatrix2.matrix4x1[3];
            verticeMatrix2.matrix4x1[2] = verticeMatrix2.matrix4x1[2]/verticeMatrix2.matrix4x1[3];
            verticeMatrix2.matrix4x1[3] = 1;
            verticeMatrix2 = viewportTransform * verticeMatrix2;
            //cout<<verticeMatrix2<<endl;
            
            
            Color colorof0 = colors[currentTriangle.vertexIds[0]];
            Color colorof1 = colors[currentTriangle.vertexIds[1]];
            Color colorof2 = colors[currentTriangle.vertexIds[2]];


            image[int(verticeMatrix.matrix4x1[0])][int(verticeMatrix.matrix4x1[1])].r = colorof0.r;
            image[int(verticeMatrix.matrix4x1[0])][int(verticeMatrix.matrix4x1[1])].g = colorof0.g;
            image[int(verticeMatrix.matrix4x1[0])][int(verticeMatrix.matrix4x1[1])].b = colorof0.b;
            image[int(verticeMatrix1.matrix4x1[0])][int(verticeMatrix1.matrix4x1[1])].r = colorof1.r;
            image[int(verticeMatrix1.matrix4x1[0])][int(verticeMatrix1.matrix4x1[1])].g = colorof1.g;
            image[int(verticeMatrix1.matrix4x1[0])][int(verticeMatrix1.matrix4x1[1])].b = colorof1.b;
            image[int(verticeMatrix2.matrix4x1[0])][int(verticeMatrix2.matrix4x1[1])].r = colorof2.r;
            image[int(verticeMatrix2.matrix4x1[0])][int(verticeMatrix2.matrix4x1[1])].g = colorof2.g;
            image[int(verticeMatrix2.matrix4x1[0])][int(verticeMatrix2.matrix4x1[1])].b = colorof2.b;
            v1.x = verticeMatrix.matrix4x1[0]; v1.y = verticeMatrix.matrix4x1[1]; v1.z = verticeMatrix.matrix4x1[2];
            v2.x = verticeMatrix1.matrix4x1[0]; v2.y = verticeMatrix1.matrix4x1[1]; v2.z = verticeMatrix1.matrix4x1[2];
            v3.x = verticeMatrix2.matrix4x1[0]; v3.y = verticeMatrix2.matrix4x1[1]; v3.z = verticeMatrix2.matrix4x1[2];
            //cout<<"V1: "<<v1.x<<", "<<v1.y<<endl;
            //cout<<"V2: "<<v2.x<<", "<<v2.y<<endl;
            rasterize(v1,v2);
            //cout<<"V1: "<<v1.x<<", "<<v1.y<<endl;
            //cout<<"V3: "<<v3.x<<", "<<v3.y<<endl;
            rasterize(v1,v3);
            //cout<<"V2: "<<v2.x<<", "<<v2.y<<endl;
            //cout<<"V3: "<<v3.x<<", "<<v3.y<<endl;
            rasterize(v2,v3);
            if(models[i].type == 1){
                rasterizeTriangle(v1,v2,v3);
            }
        }
        

    }
    
    

}


int main(int argc, char **argv) {
    int i, j;

    if (argc < 2) {
        std::cout << "Usage: ./rasterizer <scene file> <camera file>" << std::endl;
        return 1;
    }

    // read camera and scene files
    readSceneFile(argv[1]);
    readCameraFile(argv[2]);

    image = 0;

    for (i = 0; i < numberOfCameras; i++) {

        



        // allocate memory for image
        if (image) {
            for (j = 0; j < cameras[i].sizeX; j++) {
                delete image[j];
            }

            delete[] image;
        }

        image = new Color*[cameras[i].sizeX];

        if (image == NULL) {
            std::cout << "ERROR: Cannot allocate memory for image." << std::endl;
            exit(1);
        }

        for (j = 0; j < cameras[i].sizeX; j++) {
            image[j] = new Color[cameras[i].sizeY];
            if (image[j] == NULL) {
                std::cout << "ERROR: Cannot allocate memory for image." << std::endl;
                exit(1);
            }
        }


        // initialize image with basic values
        initializeImage(cameras[i]);

        // do forward rendering pipeline operations
        forwardRenderingPipeline(cameras[i]);

        // generate PPM file
        writeImageToPPMFile(cameras[i]);

        // Converts PPM image in given path to PNG file, by calling ImageMagick's 'convert' command.
        // Notice that os_type is not given as 1 (Ubuntu) or 2 (Windows), below call doesn't do conversion.
        // Change os_type to 1 or 2, after being sure that you have ImageMagick installed.
        convertPPMToPNG(cameras[i].outputFileName, 99);
    }

    return 0;

}