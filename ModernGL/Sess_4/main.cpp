#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include <math.h>
#include "GLProgram.h"
#include "Matrix4f.h"

#define WIDTH 480
#define HEIGHT 320

GLuint VBO;
GLuint IBO;

static void createVertex()
{
    Vec3f Vertices[4];
    Vertices[0] = Vec3f(-1.0, -1.0, 0.5773f);
    Vertices[1] = Vec3f(0.0, -1.0, -1.15475f);
    Vertices[2] = Vec3f(1.0, -1.0, 0.5773f);
    Vertices[3] = Vec3f(0.0, 1.0, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);


    int Indices[] = {
        0, 3, 1,
        1, 3, 2, 
        2, 3, 0,
        0, 1, 2
    };
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

}


static void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    

    static float scaleFactor = 0.0f;
    scaleFactor += 0.1f;

    Vec3f pos(0.0f, 0.0f, -3.0f);
    Vec3f target(0.0, 0.0, 2.0f);
    Vec3f up(0.0, 1.0f, 0.0f);


    Matrix4f   scaleMat, RotateMat, TransMat;
    scaleMat = Matrix4f::Scale(10.0, 10.0, 1.0);
    RotateMat = Matrix4f::RotationY(scaleFactor);
    TransMat  = Matrix4f::Translation(0.0f, 0.0f, 3.0f);

    Matrix4f  worldMat;
    worldMat = TransMat * RotateMat * scaleMat;

    Matrix4f  cameraMat;
    cameraMat = Matrix4f::lookat(pos, target, up);
    Matrix4f  projectMat;
        float mNear = 1.0f;
        float mFar =  100.0f;
        float mFovy = 60.0f;
        float ymax = mNear * tan(mFovy * 0.5);
        float ymin = - ymax;
        float xmin = ymin * ((float)WIDTH / HEIGHT);
        float xmax = -xmin;
    projectMat = Matrix4f::frustum(xmin, xmax, ymin, ymax, mNear, mFar);

    Matrix4f  viewMat;
    viewMat = projectMat * cameraMat;

    Matrix4f  mvpMat = viewMat * worldMat;


    glUniformMatrix4fv(Program::getMVPmatrix(), 1, GL_TRUE, mvpMat.getRawPointer());
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}


static void mainProcess()
{

    Program::createProgram();
    createVertex();
    glutDisplayFunc(draw);
    glutIdleFunc(draw);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(480, 320);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sess_3");

    if (glewInit() != GLEW_OK) {
        return -1;
    }

    mainProcess();

    glutMainLoop();

    return 0;
}