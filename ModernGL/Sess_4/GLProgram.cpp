
#include "GLProgram.h"
#include <string.h>

static const char vertex_shader[] = 
"attribute vec3 Position; \n"
"uniform mat4 worldMatrix; \n"
"void main() \n"
"{    \n"
"    gl_Position = worldMatrix * vec4(Position, 1.0); \n"
"} \n";

static const char fragment_shader[] = 
"void main() \n"
"{   \n"
"    gl_FragColor = vec4(1.0, 0.0, 0.0, 0.5); \n"
"}  \n";


GLint  Program::atrrIndex = 0;
GLint  Program::worldMatrix = 0;

Program::Program()
{

}

Program::~Program()
{

}

bool
Program::createProgram()
{
    GLuint shaderProgram = glCreateProgram();
    if (shaderProgram <= 0) {
        printf("create program failed\n");
        return false;
    }

    addShader(shaderProgram, vertex_shader, GL_VERTEX_SHADER);
    addShader(shaderProgram, fragment_shader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    
    glLinkProgram(shaderProgram);

	atrrIndex = glGetAttribLocation(shaderProgram, "Position");
    printf("attrrIndex;%d\n", atrrIndex);

    worldMatrix = glGetUniformLocation(shaderProgram, "worldMatrix");

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    if (!result) {
        GLchar errorLog[1024];
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        printf("link program failed %s\n", errorLog);
        return false;
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);
    if (!result) {
        GLchar errorLog[1024];
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        printf("Invalid program: %s\n", errorLog);
        return false;  
    }

    glUseProgram(shaderProgram);
    return true;

}

void 
Program::addShader(GLuint programID, const char* shaderSrc, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    if (0 == shader) {
        printf("create shader(%d) failed\n", shaderType);
        return;
    }

    const GLchar**  src = &shaderSrc;
    GLint  srcLength = strlen(shaderSrc);
    printf("shader length:%d\n", srcLength);
    glShaderSource(shader, 1, src, NULL);
    glCompileShader(shader);

    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        printf("compile shader error:%s (%d)\n", infoLog, shaderType);
        return;
    }

    glAttachShader(programID, shader);
}

GLuint Program::getMVPmatrix()
{
    return worldMatrix;
}