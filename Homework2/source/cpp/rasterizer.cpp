#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "hw2_types.h"
#include "hw2_math_ops.h"
#include "hw2_file_ops.h"
#include "functionalities.h"
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

void slope_decider(int& x0, int& y0, int& x1, int& y1){
    if((x1 - x0) == 0) return;
    double m = (y1-y0)/(x1-x0);
    if(m < 0){
        int temp = x1;
        x1 = x0;
        x0 = temp;
        temp = y1;
        y1 = y0;
        y0 = temp;
    }

}

void rasterize(Vec3 v1, Vec3 v2){
    /*int x0 = v1.x;
    int x1 = v2.x;
    int y0 = v1.y;
    int y1 = v2.y;
    //slope_decider(x0,y0,x1,y1);
    int y = y0;
    int d = 2*(y0 - y1) + (x1-x0);
    //cout<<"HII"<<endl;
    if(x0 > x1 && y0 > y1){
        y = y1;
        for(int x =x1; x<x0; x++){
            //cout<<"ILK FOR "<<"X: "<<x<<" Y: "<<y<<endl;
            Color color = color_decider(v1,v2);
            image[x][y].r = color.r;
            image[x][y].g = color.g;
            image[x][y].b = color.b;
            if(d>0){
                y+=1;
                d+= 2*((y0 -y1) + (x1-x0)); 
            }
            else{
                d+= 2*(y0-y1);
            }
        }
    }
    else{
        for(int x =x0; x<x1; x++){
        //cout<<"X: "<<x<<" Y: "<<y<<endl;
        Color color = color_decider(v1,v2);
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

    }*/
    
    

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
            Matrix4x4 totalTransform;
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
            if(j == 3){
                cout<<"V1: "<<v1.x<<", "<<v1.y<<endl;
                cout<<"V2: "<<v2.x<<", "<<v2.y<<endl;
                rasterize(v1,v2);
                cout<<"V1: "<<v1.x<<", "<<v1.y<<endl;
                cout<<"V3: "<<v3.x<<", "<<v3.y<<endl;
                rasterize(v1,v3);
                cout<<"V2: "<<v2.x<<", "<<v2.y<<endl;
                cout<<"V3: "<<v3.x<<", "<<v3.y<<endl;
                rasterize(v2,v3);
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

    for (i = 0; i < 1; i++) {

        



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
