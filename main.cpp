#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <limits>
#include <iostream>
#include <cmath>

#include <stdint.h>
#include "raylib.h"

#define MIN_INTERVAL (1.0 / 100.0)
#define MAX_LATENCY   0.5


class Vertex {
    public:
        Vertex();
        Vertex(float, float, float, float, float, float, float,float, float, float);
		friend std::ostream& operator<<(std::ostream& os, const Vertex& v);
        float x = 0.0f;   // coordinate in 3D space
        float y = 0.0f;
        float z = 0.0f;

        float r = 0.0f;   // color
        float g = 0.0f;
        float b = 0.0f;
        float a = 1.0f;

        float nx = 0.0f;  // normal vector (using for lighting)
        float ny = 0.0f;
        float nz = 0.0f;
};

class Triangle{
    public:
        Triangle();
        Vertex vertices[3];
		friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
};

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
    os << "Vertex: x=" << v.x << " y=" << v.y << " z=" << v.z << std::endl;
	return os;  
}

std::ostream& operator<<(std::ostream& os, const Triangle& t)
{  
	//os << dt.mo << '/' << dt.da << '/' << dt.yr;
    for (int i = 0; i < 3; i++)
    {
	    os << t.vertices[i];
    }
	return os;  
} 


Vertex::Vertex() {}
Vertex::Vertex(float x, float y, float z, float r, float g, float b, float a, float nx, float ny, float nz)
{
    this->x = x;
    this->y = y;
    this->z = z;

    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;

    this->nx = nx;
    this->ny = ny;
    this->nz = nz;
}


Triangle::Triangle()
{

}

const int screenWidth = 1024;
const int screenHeight = 600;
const Color BACKGROUND = {0, 166, 215};

std::map<int,Triangle> triangles;

float modelX = 0;
float modelY = 0;
float modelZ = 0;

float modelScaleX = 1;
float modelScaleY = 1;
float modelScaleZ = 1;

float modelRotateX = 0;
float modelRotateY = 0;
float modelRotateZ = 0;

float modelOriginX = 10;
float modelOriginY = 0;
float modelOriginZ = 10;

float cameraX =  0;
float cameraY =  20;
float cameraZ = -20;

float ambientR = 1;
float ambientG = 1;
float ambientB = 1;
float ambientIntensity = 0.2;

float diffuseR = 1;
float diffuseG = 1;
float diffuseB = 1;
float diffuseIntensity = 0.8;

float diffuseX = 0;    // direction of the diffuse light
float diffuseY = 0;   // (this vector should have length 1)
float diffuseZ = 1;

float depthBuffer[screenWidth * screenHeight] = {0};


void Update(float dx)
{

}


void Init()
{

    Triangle tr_0;
    tr_0.vertices[0] = Vertex(-10, -10, 10, 0, 0, 1, 1, 0, 0, 1);
    tr_0.vertices[1] = Vertex(-10,  10, 10, 0, 0, 1, 1, 0, 0, 1);
    tr_0.vertices[2] = Vertex( 10, -10, 10, 0, 0, 1, 1, 0, 0, 1);
    triangles[0] = tr_0;

    Triangle tr_1;
    tr_1.vertices[0] = Vertex(-10,  10, 10, 0, 0, 1, 1, 0, 0, 1);
    tr_1.vertices[1] = Vertex( 10, -10, 10, 0, 0, 1, 1, 0, 0, 1);
    tr_1.vertices[2] = Vertex( 10,  10, 10, 0, 0, 1, 1, 0, 0, 1);
    triangles[1] = tr_1;

    Triangle tr_2;
    tr_2.vertices[0] = Vertex(-10, -10, -10, 1, 0, 0, 1, 0, 0, -1);
    tr_2.vertices[1] = Vertex( 10, -10, -10, 0, 1, 0, 1, 0, 0, -1);
    tr_2.vertices[2] = Vertex( 10,  10, -10, 0, 0, 1, 1, 0, 0, -1);
    triangles[2] = tr_2;

    Triangle tr_3;
    tr_3.vertices[0] = Vertex(-10, -10, -10, 1, 1, 0, 1, 0, 0, -1);
    tr_3.vertices[1] = Vertex( 10,  10, -10, 0, 1, 1, 1, 0, 0, -1);
    tr_3.vertices[2] = Vertex(-10,  10, -10, 1, 0, 1, 1, 0, 0, -1);
    triangles[3] = tr_3;

    Triangle tr_4;
    tr_4.vertices[0] = Vertex(-10,  10, -10, 1, 0, 0, 1, 0, 1, 0);
    tr_4.vertices[1] = Vertex(-10,  10,  10, 1, 0, 0, 1, 0, 1, 0);
    tr_4.vertices[2] = Vertex( 10,  10, -10, 1, 0, 0, 1, 0, 1, 0);
    triangles[4] = tr_4;

    Triangle tr_5;
    tr_5.vertices[0] = Vertex(-10, 10,  10, 1, 0, 0, 1, 0, 1, 0);
    tr_5.vertices[1] = Vertex( 10, 10, -10, 1, 0, 0, 1, 0, 1, 0);
    tr_5.vertices[2] = Vertex( 10, 10,  10, 1, 0, 0, 1, 0, 1, 0);
    triangles[5] = tr_5;

    Triangle tr_6;
    tr_6.vertices[0] = Vertex(-10, -10, -10, 1, 1, 1, 1, 0, -1, 0);
    tr_6.vertices[1] = Vertex( 10, -10, -10, 1, 1, 1, 1, 0, -1, 0);
    tr_6.vertices[2] = Vertex(-10, -10,  10, 1, 1, 1, 1, 0, -1, 0);
    triangles[6] = tr_6;

    Triangle tr_7;
    tr_7.vertices[0] = Vertex(-10, -10,  10, 1, 1, 1, 1, 0, -1, 0);
    tr_7.vertices[1] = Vertex( 10, -10,  10, 1, 1, 1, 1, 0, -1, 0);
    tr_7.vertices[2] = Vertex( 10, -10, -10, 1, 1, 1, 1, 0, -1, 0);
    triangles[7] = tr_7;

    Triangle tr_8;
    tr_8.vertices[0] = Vertex(10, -10, -10, 0, 1, 0, 1, 1, 0, 0);
    tr_8.vertices[1] = Vertex(10, -10,  10, 0, 1, 0, 1, 1, 0, 0);
    tr_8.vertices[2] = Vertex(10,  10, -10, 0, 1, 0, 1, 1, 0, 0);
    triangles[8] = tr_8;

    Triangle tr_9;
    tr_9.vertices[0] = Vertex(10, -10,  10, 0, 1, 0, 1, 1, 0, 0);
    tr_9.vertices[1] = Vertex(10,  10, -10, 0, 1, 0, 1, 1, 0, 0);
    tr_9.vertices[2] = Vertex(10,  10,  10, 0, 1, 0, 1, 1, 0, 0);
    triangles[9] = tr_9;

    // The yellow side has normal vectors that point in different directions,
    // which makes it appear rounded when lighting is applied. For the other
    // sides all vertices have the same normal vectors, making them appear flat.
    Triangle tr_10;
    tr_10.vertices[0] = Vertex(-10, -10, -10, 1, 1, 0, 1, -0.577, -0.577, -0.577);
    tr_10.vertices[1] = Vertex(-10,  10, -10, 1, 1, 0, 1, -0.577,  0.577, -0.577);
    tr_10.vertices[2] = Vertex(-10, -10,  10, 1, 1, 0, 1, -0.577, -0.577,  0.577);
    triangles[10] = tr_10;

    Triangle tr_11;
    tr_11.vertices[0] = Vertex(-10, -10,  10, 1, 1, 0, 1, -0.577, -0.577,  0.577);
    tr_11.vertices[1] = Vertex(-10,  10,  10, 1, 1, 0, 1, -0.577,  0.577,  0.577);
    tr_11.vertices[2] = Vertex(-10,  10, -10, 1, 1, 0, 1, -0.577,  0.577, -0.577);
    triangles[11] = tr_11;


    for (int i = 0; i < screenHeight * screenHeight; i++)
    {
        depthBuffer[i] = std::numeric_limits<float>::max();
    }


    //--------- Transformation to view space ----------

    std::map<int,Triangle> transformed;
    transformed = triangles;

	for(auto &mTriangle : transformed)
	{
        Triangle newTriangle;

        std::cout << mTriangle.first << " Triangle" << std::endl;
        std::cout << mTriangle.second << std::endl;

        for (int i = 0; i < 3; i++)
        {
            Vertex newVertex = mTriangle.second.vertices[i];

            /* Translation */
            newVertex.x -= modelOriginX;
            newVertex.y -= modelOriginY;
            newVertex.z -= modelOriginZ;

            /* Scaling */
            newVertex.x *= modelScaleX;
            newVertex.y *= modelScaleY;
            newVertex.z *= modelScaleZ;

            /* Rotations */
            // Rotate about the X-axis.
            float tempA =  cos(modelRotateX) * newVertex.y + sin(modelRotateX) * newVertex.z;
            float tempB = -sin(modelRotateX) * newVertex.y + cos(modelRotateX) * newVertex.z;
            newVertex.y = tempA;
            newVertex.z = tempB;

            // Rotate about the Y-axis:
            tempA =  cos(modelRotateY) * newVertex.x + sin(modelRotateY) * newVertex.z;
            tempB = -sin(modelRotateY) * newVertex.x + cos(modelRotateY) * newVertex.z;
            newVertex.x = tempA;
            newVertex.z = tempB;

            // Rotate about the Z-axis:
            tempA =  cos(modelRotateZ) * newVertex.x + sin(modelRotateZ) * newVertex.y;
            tempB = -sin(modelRotateZ) * newVertex.x + cos(modelRotateZ) * newVertex.y;
            newVertex.x = tempA;
            newVertex.y = tempB;

            /* Normal Vector recalc */
            tempA =  cos(modelRotateY)*newVertex.nx + sin(modelRotateY)*newVertex.nz;
            tempB = -sin(modelRotateY)*newVertex.nx + cos(modelRotateY)*newVertex.nz;
            newVertex.nx = tempA;
            newVertex.nz = tempB;

            /* Translation (moving) */
            newVertex.x += modelX;
            newVertex.y += modelY;
            newVertex.z += modelZ;

            newTriangle.vertices[i] = newVertex;
        }

        mTriangle.second = newTriangle;

	}

    //--------- end Transformation ----------
    //--------- Transformation to camera space ----------
    
	for(auto &mTriangle : transformed)
	{
        Triangle newTriangle;

        std::cout << mTriangle.first << " Triangle" << std::endl;
        std::cout << mTriangle.second << std::endl;

        for (int i = 0; i < 3; i++)
        {
            Vertex newVertex = mTriangle.second.vertices[i];
            
            // Move everything in the world opposite to the camera, i.e. if the
            // camera moves to the left, everything else moves to the right.
            newVertex.x -= cameraX;
            newVertex.y -= cameraY;
            newVertex.z -= cameraZ;

            // Likewise, you can perform rotations as well. If the camera rotates
            // to the left with angle alpha, everything else rotates away from the
            // camera to the right with angle -alpha. (I did not implement that in
            // this demo.)

            newTriangle.vertices[i] = newVertex;

        }

        mTriangle.second = newTriangle;
    }
    
    //--------- end Transformation ----------
    //--------- Transformation to screen space (pixels) ----------

	for(auto &mTriangle : transformed)
	{
        Triangle newTriangle;

        std::cout << mTriangle.first << " Triangle" << std::endl;
        std::cout << mTriangle.second << std::endl;

        for (int i = 0; i < 3; i++)
        {
            Vertex newVertex = mTriangle.second.vertices[i];

            newVertex.x /= (newVertex.z + 100) * 0.01;
            newVertex.y /= (newVertex.z + 100) * 0.01;

            newVertex.x *= float(screenHeight) / 80;
            newVertex.y *= float(screenHeight) / 80;

            newVertex.x += float(screenWidth / 2);
            newVertex.y += float(screenHeight / 2);

            newTriangle.vertices[i] = newVertex;

        }

        mTriangle.second = newTriangle;
    }

    //--------- end Transformation ----------

    while (!WindowShouldClose()) {
        Update(GetFrameTime());

        // Draw
        BeginDrawing();

            // Actually draw things
            ClearBackground(BACKGROUND);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();
}


void Draw()
{
}

int main(int argc, char **argv)
{
    SetConfigFlags(FLAG_VSYNC_HINT); // Use before InitWindow()
    InitWindow(screenWidth, screenHeight, "3D-test");
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second

    Init();
    Draw();

    return 0;
}
