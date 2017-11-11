#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math.h"

GLuint VBO;

static void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableVertexAttribArray(0);
    //glFlush();
    glutSwapBuffers();
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[1];
    Vertices[0] = Vector3f(0.0, 0.0, 0.0);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(480, 320);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sess_2");
    glutDisplayFunc(RenderScene);
    GLenum ret = glewInit();
    if (ret != GLEW_OK) {
        printf("GLEW INIT Failed\n");
        return -1;
    }
    glClearColor(0.0, 0.0, 0.0, 0.0);
    CreateVertexBuffer();
    glutMainLoop();
    return 0;
}


