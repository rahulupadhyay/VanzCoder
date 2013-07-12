//
//  main.cpp
//  CursoCG
//
//  Created by DBAPPZ on 13/05/13.
//  Copyright (c) 2013 Christian Hess. All rights reserved.
//

#include <time.h>
#include <iostream>

// GLTools
#include <GLTools.h>
#include <GLShaderManager.h>    // Shader Manager Class
#include <GLFrustum.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>

// OpenGL
// #include <OpenGL/OpenGL.h>
#include <glut.h>

#include "ObjParserWavefront.h"

void CreateBatch();

// Classes auxiliares do GLTools
GLShaderManager		shaderManager;     //The shader manager of GLTools
GLFrame				cameraFrame;       //Frame of reference for the camera
GLFrustum			viewFrustum;       //View frustum
GLMatrixStack		modelViewMatrix;   //Modelview Matrix
GLMatrixStack		projectionMatrix;  //Projection Matrix
GLGeometryTransform transformPipeline; //Geometry Transform Pipeline

// Parametros da camera
M3DVector3f			gCameraPosition =   {0.0f, 0.5f, 0.0f};    //Camera position
M3DVector3f			gCameraLookAt =     {0.0f, 0.0f, 1.0f};     //Reference point to look at
M3DVector3f			gCameraUp =         {0.0f, 1.0f, 0.0f};	    //Camera up direction
GLfloat				gCameraYaw =        0.0f;					//Carmera Yaw


// Batchs
GLBatch				axisBatch;			// Batch de geometria dos eixos
GLBatch				linesBatch;			// Batch de geometria das linhas
GLTriangleBatch		sphereBatch;        // Batch de geometria da esfera
GLBatch             spaceBatch;

// #MOD
GLBatch             cubeBatch;

// Variaveis auxiliares
int                 windowWidth = 600;          // Largura da janela
int                 windowHeight = 500;         // Altura da janela
clock_t             lastClock = clock();        // Ticks do relógio
float               updateFrequency = 1.0;      // Frequencia de atualização da lógica do game, em segundos

GLuint textureIndex1;
GLuint textureIndex2;

GLuint shaderID;

GLuint uniformTextUnit1;
GLuint uniformTextUnit2;

GLuint uniformMVPMatrix;

GLuint uniformMVMatrix;
GLuint uniformPMatrix;
GLuint uniformNMatrix;

ObjParserWavefront      *parser = new ObjParserWavefront();
ObjModel                *model = new ObjModel();
GLfloat                 *vertices;
GLfloat                 *textures;
GLuint                  vertice_count;

M3DVector4f diffuseColor = {0.7, 0.5, 0.5, 1.0};
M3DVector4f ambientColor = {0.4, 0.4, 0.4, 1.0};
M3DVector4f specularColor = {10.0, 4.0, 4.0, 1.0};

M3DVector3f lightPosition = {10, 5, 8};

GLuint uniformLightPosition;
GLuint uniformAmbientColor;
GLuint uniformDiffuseColor;
GLuint uniformSpecularColor;

GLuint vbo_vertex;
GLuint vbo_textures;

float rotation = 0.0;


#pragma mark KeyboardKeys

void KeyboardFunc(unsigned char key, int x, int y) {
    
	switch(key) {
		case 'a':
			break;
		case 'w':
			break;
		case 's':
			break;
	}
}

void SpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP:
			gCameraPosition[0] += cos(gCameraYaw) * 3.5f;
			gCameraPosition[2] += sin(gCameraYaw) * 3.5f;
			break;
		case GLUT_KEY_DOWN:
			gCameraPosition[0] -= cos(gCameraYaw) * 3.5f;
			gCameraPosition[2] -= sin(gCameraYaw) * 0.5f;
			break;
		case GLUT_KEY_LEFT:
			gCameraYaw -= 0.5f;
			break;
		case GLUT_KEY_RIGHT:
			gCameraYaw += 0.5f;
            break;
	}
}

#pragma mark CameraSetup

void ChangeSize(int w, int h) {
	if (h == 0) {
		h = 1;
	}
    
	windowWidth = w;
	windowHeight = h;
    viewFrustum.SetPerspective (45.0f, float(windowWidth)/float(windowHeight), 0.1f, 1000.0f);
}

void CameraUpdate(void) {
    projectionMatrix.LoadIdentity();
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    
	M3DVector3f forwardVector = {0.0f, 0.0f, 1.0f};
    
	gCameraLookAt[0] = gCameraPosition[0] + cos(gCameraYaw);
	gCameraLookAt[1] = gCameraPosition[1];
	gCameraLookAt[2] = gCameraPosition[2] + sin(gCameraYaw);
    
	m3dSubtractVectors3(forwardVector, gCameraLookAt, gCameraPosition);
	m3dNormalizeVector3(forwardVector);
    
	cameraFrame.SetOrigin(gCameraPosition);
	cameraFrame.SetForwardVector(forwardVector);
	cameraFrame.SetUpVector(gCameraUp);
	
	M3DMatrix44f cameraMatrix;
	cameraFrame.GetCameraMatrix(cameraMatrix);
    
	modelViewMatrix.LoadIdentity();
	modelViewMatrix.LoadMatrix(cameraMatrix);
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

#pragma mark GameRender

void GameRender(void) {
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, windowWidth, windowHeight);
    
    shaderManager.UseStockShader(GLT_SHADER_SHADED, transformPipeline.GetModelViewProjectionMatrix());
    linesBatch.Draw();
	axisBatch.Draw();
    
    M3DVector4f color = {0.6, 0.1, 0.1, 1.0};
    
    // ESFERA VERMELHA
    modelViewMatrix.PushMatrix();
    modelViewMatrix.Translate(10, 2, 10);
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), color);
    sphereBatch.Draw();
    modelViewMatrix.PopMatrix();
    
    // ESFERA TEXTURIZADA
    modelViewMatrix.PushMatrix();
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex2);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureIndex2);
    
    glUseProgram(shaderID);

    modelViewMatrix.Translate(-5, 0, 2);
    modelViewMatrix.Rotate(rotation, 0, 1, 0);
    
    glUniformMatrix4fv(uniformMVMatrix, 1, GL_FALSE, transformPipeline.GetModelViewMatrix());
    glUniformMatrix4fv(uniformPMatrix, 1, GL_FALSE, transformPipeline.GetProjectionMatrix());
    
    modelViewMatrix.PushMatrix();
    modelViewMatrix.LoadIdentity();
    modelViewMatrix.Rotate(rotation, 0, 1, 0);

    glUniformMatrix3fv(uniformNMatrix, 1, GL_FALSE, transformPipeline.GetNormalMatrix());
    
    modelViewMatrix.PopMatrix();
    
    rotation += 0.01;

    if(rotation > 360)
        rotation = 0;
    
    glUniform1i(uniformTextUnit1, 0);
    glUniform1i(uniformTextUnit2, 1);
    
    glUniform4fv(uniformAmbientColor, 1, ambientColor);
    glUniform4fv(uniformDiffuseColor, 1, diffuseColor);
    glUniform4fv(uniformSpecularColor, 1, specularColor);
    glUniform3fv(uniformLightPosition, 1, lightPosition);
    
    glEnableVertexAttribArray(GLT_ATTRIBUTE_VERTEX);
    glBindBuffer(GL_VERTEX_ARRAY, vbo_vertex);
    
    glEnableVertexAttribArray(GLT_ATTRIBUTE_TEXTURE0);
    glBindBuffer(GL_VERTEX_ARRAY, vbo_textures);

    glDrawArrays(GL_TRIANGLES, 0, vertice_count*3);
    
    glDisableVertexAttribArray(GLT_ATTRIBUTE_VERTEX);
    glDisableVertexAttribArray(GLT_ATTRIBUTE_TEXTURE0);
    
    modelViewMatrix.PopMatrix();
    
    glutSwapBuffers();
}

# pragma mark GameLogic

void GameLogic(void) {
    
}

# pragma mark MainCycle

void MainCycle(void){
    clock_t nowClock = clock();
    // Calcula quanto tempo levou desde a ultima chamada
    // (TICKS_AGORA - ULTIMO_TICKS) / TICKS_POR_SEGUNDO * 100
    float lastTimeUpdate = (((float)nowClock - (float)lastClock) / CLOCKS_PER_SEC * 100);
    
    // Verifica se deve atualizar a lógica
    if(lastTimeUpdate > updateFrequency){
        GameLogic();
        lastClock = nowClock;
    }
    
    CameraUpdate();
	GameRender();
}

GLuint LoadTexture(const char* textureFileName, GLenum textureIndexUnit){
    GLuint texIndex = 0;
    GLint textureWidth;
    GLint textureHeight;
    GLint components;
    GLenum eFormat;
    
    GLbyte *textureData = gltReadTGABits(textureFileName, &textureWidth, &textureHeight, &components, &eFormat);
    
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(textureIndexUnit);
    
    glGenTextures(1, &texIndex);
    glBindTexture(GL_TEXTURE_2D, texIndex);
    
    glTexImage2D(GL_TEXTURE_2D, 0, components, textureWidth, textureHeight, 0, eFormat, GL_UNSIGNED_BYTE, textureData);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    free(textureData);
    
    return texIndex;
}

GLuint LoadShader(std::string vertexShaderStr, std::string fragmentShaderStr){
    
    GLuint programID;
    GLuint vertexShader;
    GLuint fragmentShader;
    
    GLint status;
    char log[1024];
    
    // VERTEX SHADER
    const char *vertexShaderChar = vertexShaderStr.c_str();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderChar, NULL);
    glCompileShader(vertexShader);
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE){
        glGetShaderInfoLog(vertexShader, 1024, NULL, log);
        fprintf(stderr, "Vertex compile failed:\n%s\n", log);
        glDeleteShader(vertexShader);
        return 0;
    }
    
    // FRAGMENT SHADER
    const char *fragmenShaderChar = fragmentShaderStr.c_str();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmenShaderChar, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE){
        glGetShaderInfoLog(fragmentShader, 1024, NULL, log);
        fprintf(stderr, "Fragment compile failed:\n%s\n", log);
        glDeleteShader(fragmentShader);
        return 0;
    }
    
    programID = glCreateProgram();
    
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    
    glBindAttribLocation(programID, GLT_ATTRIBUTE_VERTEX, "vVertex");
    glBindAttribLocation(programID, GLT_ATTRIBUTE_TEXTURE0, "vTexCoord0");
    glBindAttribLocation(programID, GLT_ATTRIBUTE_NORMAL, "vNormal");
    
    glLinkProgram(programID);
    
    glGetProgramiv(programID, GL_LINK_STATUS, &status);
    
    if(status == GL_FALSE){
        glGetProgramInfoLog(programID, 1024, NULL, log);
        fprintf(stderr, "Link failed:\n%s\n", log);
        glDeleteProgram(programID);
        return 0;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    glUseProgram(programID);
    uniformMVMatrix = glGetUniformLocation(programID, "mvMatrix");
    uniformPMatrix = glGetUniformLocation(programID, "pMatrix");
    uniformNMatrix = glGetUniformLocation(programID, "nMatrix");

    uniformTextUnit1 = glGetUniformLocation(programID, "textureUnit0");
    uniformTextUnit2 = glGetUniformLocation(programID, "textureUnit1");
    
    uniformLightPosition = glGetUniformLocation(programID, "lightPosition");
    uniformAmbientColor = glGetUniformLocation(programID, "ambientColor");
    uniformDiffuseColor = glGetUniformLocation(programID, "diffuseColor");
    uniformSpecularColor = glGetUniformLocation(programID, "specularColor");
    
    return programID;
}

std::string ReadFile(const char *fileName){
    FILE *f = fopen(fileName, "rb");
    std::string content;
    
    if(f){
        ssize_t readCount;
        char *line = NULL;
        size_t len = 0;
        
        while((readCount = getline(&line, &len, f)) != EOF){
            content += line;
        }
        
        fclose(f);
    }
    
    return content;
}

#pragma mark Init

void Init() {
	glEnable(GL_DEPTH_TEST); // Habilita o buffer de teste de profundidade
	glEnable(GL_CULL_FACE); // Habilita o culling de faces, por questoes de performance, desenhando apenas as faces da frente
    
    // Inicializa o gerenciador de shaders
    shaderManager.InitializeStockShaders();
    
    textureIndex1 = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/space/data/texture/sun.tga", GL_TEXTURE0);
    textureIndex2 = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/space/data/texture/earth.tga", GL_TEXTURE1);
    
    std::string vertexShader = ReadFile("/home/vanz/gitroot/VanzCoder/opengl/space/vertex.v1.vsh");
    std::string fragmentShader = ReadFile("/home/vanz/gitroot/VanzCoder/opengl/space/fragment.v1.fsh");
    
    shaderID = LoadShader(vertexShader, fragmentShader);
    
    CreateBatch();
}

#pragma mark Main

int main(int argc, char * argv[]){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("CursoCG");
    
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(MainCycle);
	glutIdleFunc(MainCycle);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(KeyboardFunc);
    
    GLenum err = glewInit();
    
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}
    
	Init();
    
	glutMainLoop();
    return 0;
}


#pragma mark CreateBatch

void CreateBatch(){
    parser->parse("/home/vanz/gitroot/VanzCoder/opengl/space/spaceship.obj", model);
    ObjGroup *group = model->get_group(1);

    GLuint texturesInt;
    
    vertices = new GLfloat[group->triangles * 9];
    textures = new GLfloat[group->triangles * 6];
    vertice_count = group->triangles;
    
    group->get_triangles(vertices);
    group->get_textures(textures, texturesInt);

    glGenBuffers(1, &vbo_vertex);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * group->triangles*9, vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(GLT_ATTRIBUTE_VERTEX);
    
    glVertexAttribPointer(GLT_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);

    glDisableVertexAttribArray(GLT_ATTRIBUTE_VERTEX);
    
    
    glGenBuffers(1, &vbo_textures);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_textures);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * group->triangles*6, textures, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(GLT_ATTRIBUTE_TEXTURE0);
    
    glVertexAttribPointer(GLT_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, 0);
    
    glDisableVertexAttribArray(GLT_ATTRIBUTE_TEXTURE0);
    
    
    
    // Cria uma esfera
    gltMakeSphere(sphereBatch, 1.0f, 26, 13);
    gltMakeCube(cubeBatch, 5);
    
    // Cria os eixos
    /* Initialise the axis batch with the vertices and color */
	axisBatch.Begin(GL_LINES, 6);
    
    // x Axis
	axisBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	axisBatch.Vertex3f(0.0f,0.0f, 0.0f);
    axisBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	axisBatch.Vertex3f(1.0f,0.0f, 0.0f);
    
	// y Axis
    axisBatch.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
	axisBatch.Vertex3f(0.0f,0.0f, 0.0f);
    axisBatch.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
	axisBatch.Vertex3f(0.0f,1.0f, 0.0f);
    
	// z Axis
    axisBatch.Color4f(0.0f, 0.0f, 1.0f, 1.0f);
	axisBatch.Vertex3f(0.0f,0.0f, 1.0f);
    axisBatch.Color4f(0.0f, 0.0f, 1.0f, 1.0f);
   	axisBatch.Vertex3f(0.0f,0.0f, 0.0f);
	axisBatch.End();
    
    // Cria as linhas
	linesBatch.Begin(GL_LINES, 84);
	linesBatch.Color4f(0.5,0.5,0.5,1.0f);
	for (int i=-10;i<=10;i++) {
        linesBatch.Vertex3f(100*i,-1,-1000);
        linesBatch.Vertex3f(100*i,-1,1000);
        linesBatch.Vertex3f(-1000,-1,100*i);
        linesBatch.Vertex3f(1000,-1,100*i);
	}
	linesBatch.End();
} 