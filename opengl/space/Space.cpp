#include <stdio.h>
#include <string.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ObjParserWavefront.h"

void RenderSceneCB();
void InitializeGlutCallbacks();
void CreateVertexBuffer();
void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
void CompileShaders();
void MainCycle();
void UpdateCamera();
void KeyboardFunc(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);
void init();

//-----------Janela--------------------
int windowWidth = 1024;
int windowHeight = 768;
//-------------------------------------
//--------------Camera-----------------

float posicaoCamera[3] = {0.0f, 0.0f,-20.0f};  // posicao da camera
float posicaoAlvoCamera[3] = {0.0f, 0.0f,  0.0f};  // para onde a camera esta olhando
float posicaoVetorUpCamera[3] = {0.0f, 1.0f,  0.0f}; // parte de cima da camera

float fatorMovimentacao = 1.0f;
double fovy = 45.0;
double aspect = 1.0;
double zNear = 1.0;
double zFar = 300.0;


//-------------------------------------
//-------------Luz---------------------
GLfloat pos[4] = {0.0, 3.0, 0.0, 1};
//-------------------------------------
//-------------Objetos do mundo--------
ObjParserWavefront parser;  // Obj auxiliar para carregar arquivos wavefront
ObjFile* nave; // nave
ObjFile* asteroid;  //asteroid

//-------------------------------------
GLdouble projection[16], modelview[16];

GLuint VBO;

void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_LIGHTING);
    asteroid->draw();

    glDisable(GL_LIGHTING);
    glutSwapBuffers();
}

void UpdateCamera()
{
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, zNear, zFar);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt ( posicaoCamera[0],        posicaoCamera[1],        posicaoCamera[2],
                posicaoAlvoCamera[0],    posicaoAlvoCamera[1],    posicaoAlvoCamera[2],
                posicaoVetorUpCamera[0], posicaoVetorUpCamera[1], posicaoVetorUpCamera[2]);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glClearColor(0.2, 0.2, 0.2, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
   

}


void MainCycle()
{
    // glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    UpdateCamera();
    RenderSceneCB();
}

 void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

 void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    // AddShader(ShaderProgram, pVS, GL_VERTEX_SHADER);
    // AddShader(ShaderProgram, pFS, GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);
}

void SpecialKeys(int key, int x, int y) {
    switch(key) {
        std::cout << "Tecla precionada" << std::endl;
        case GLUT_KEY_UP:
            posicaoCamera[1] += fatorMovimentacao;
            // gCameraPosition[0] += cos(gCameraYaw) * 3.5f;
            // gCameraPosition[2] += sin(gCameraYaw) * 3.5f;
            break;
        case GLUT_KEY_DOWN:
            posicaoCamera[1] -= fatorMovimentacao;
            // gCameraPosition[0] -= cos(gCameraYaw) * 3.5f;
            // gCameraPosition[2] -= sin(gCameraYaw) * 0.5f;
            break;
        case GLUT_KEY_LEFT:
            posicaoCamera[0] += fatorMovimentacao;
            // gCameraYaw -= 0.5f;
            break;
        case GLUT_KEY_RIGHT:
            posicaoCamera[0] -= fatorMovimentacao;
            // gCameraYaw += 0.5f;
            break;
    }
}

void init()
{
    //Carrega obj da asteroid
    asteroid = new ObjFile("/home/vanz/gitroot/VanzCoder/opengl/space/asteroid.obj");

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 04");

    glutDisplayFunc(MainCycle);
    glutIdleFunc(MainCycle);
    glutSpecialFunc(SpecialKeys);
    //glutKeyboardFunc(KeyboardFunc);

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }
    printf("GL version: %s\n", glGetString(GL_VERSION));

    init();
    glutMainLoop();
    return 0;
}

