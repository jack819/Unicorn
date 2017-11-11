#include <GL/glew.h>
#include <stdio.h>

class Program 
{
public:
     Program();
     ~Program();

     static bool createProgram();
     static void addShader(GLuint programID, const char* shaderSrc, GLenum shaderType);

     static GLuint getMVPmatrix();

public:
    static GLint  atrrIndex;
    static GLint  worldMatrix;

};