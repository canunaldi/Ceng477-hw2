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


void forwardRenderingPipeline(Camera cam) {
    Matrix4x4 camTransform = calculatecamTransform(cam);
    cout<<camTransform<<endl;
    Matrix4x4 persTransform = calculatePersTransform(cam);
    cout<<persTransform<<endl;
    Matrix4x4 viewportTransform = calculateViewPort(cam);
    cout<<viewportTransform<<endl;
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
