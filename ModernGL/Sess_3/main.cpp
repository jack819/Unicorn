#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include "math.h"

static const char vertex_shader[] = 
"attribute vec3 Position; \n"
"void main() \n"
"{    \n"
"    gl_Position = vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0); \n"
"} \n";

static const char fragment_shader[] = 
"void main() \n"
"{   \n"
"    gl_FragColor = vec4(1.0, 0.0, 0.0, 0.5); \n"
"}  \n";



GLuint VBO;
GLint  atrrIndex;

static void createVertex()
{
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.0, -1.0, 0.0);
    Vertices[1] = Vector3f(1.0, -1.0, 0.0);
    Vertices[2] = Vector3f(0.0, 1.0, 0.0);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void addShader(GLuint programID, const char* shaderSrc, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    if (0 == shader) {
        printf("create shader(%d) failed\n", shaderType);
        exit(1);
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
        exit(1);
    }

    glAttachShader(programID, shader);
}

static void loadProgramAndShaders()
{
    GLuint shaderProgram = glCreateProgram();
    if (0 == shaderProgram) {
        printf("Create GL program failed\n");
        exit(1);
    }
    
    addShader(shaderProgram, vertex_shader, GL_VERTEX_SHADER);
    addShader(shaderProgram, fragment_shader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    
    glLinkProgram(shaderProgram);

	atrrIndex = glGetAttribLocation(shaderProgram, "Position");
    printf("attrrIndex;%d\n", atrrIndex);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    if (!result) {
        GLchar errorLog[1024];
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        printf("link program failed %s\n", errorLog);
        exit(1);
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);
    if (!result) {
        GLchar errorLog[1024];
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        printf("Invalid program: %s\n", errorLog);
        exit(1);  
    }

    glUseProgram(shaderProgram);
    return;
}

static void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnableVertexAttribArray(atrrIndex);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(atrrIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(atrrIndex);
    glutSwapBuffers();
}

static void Render()
{
    // createVertex();

    // loadProgramAndShaders();

    draw();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(480, 320);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sess_3");

    glutDisplayFunc(Render);

    GLenum ret = glewInit();
    if (ret != GLEW_OK) {
        printf("gLew init failed\n");
        return -1;
    }
    createVertex();

    loadProgramAndShaders();
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutMainLoop();

    return 0;
}