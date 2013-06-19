//
//  CursoCG.cpp
//  CursoCG
//
//  Created by DBAPPZ on 13/05/13.
//  Copyright (c) 2013 Christian Hess. All rights reserved.
//

#include <time.h>
#include <iostream>
#include <string>
#include <fstream>

// GLTools
#include <GLTools.h>
#include <GLShaderManager.h>    // Shader Manager Class
#include <GLFrustum.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>

#include <glut.h>

#include <WaveFrontUtils.h>

void CreateBatch();

// Classes auxiliares do GLTools
GLShaderManager		shaderManager;     //The shader manager of GLTools
GLFrame			cameraFrame;       //Frame of reference for the camera
GLFrustum		viewFrustum;       //View frustum
GLMatrixStack		modelViewMatrix;   //Modelview Matrix
GLMatrixStack		projectionMatrix;  //Projection Matrix
GLGeometryTransform transformPipeline; //Geometry Transform Pipeline

// Parametros da camera
M3DVector3f		gCameraPosition =   {0.0f, 0.5f, 5.0f};    //Camera position
M3DVector3f		gCameraLookAt =     {0.0f, 0.0f, 0.0f};     //Reference point to look at
M3DVector3f		gCameraUp =         {0.0f, 1.0f, 0.0f};	    //Camera up direction
GLfloat			gCameraYaw =        0.0f;					//Carmera Yaw


// Batchs
GLBatch			axisBatch;			// Batch de geometria dos eixos
GLBatch			linesBatch;			// Batch de geometria das linhas
GLTriangleBatch		sphereBatch;        // Batch de geometria da esfera

// Variaveis auxiliares
int                 windowWidth = 800;          // Largura da janela
int                 windowHeight = 600;         // Altura da janela
clock_t             lastClock = clock();        // Ticks do relógio
float               updateFrequency = 1.0;      // Frequencia de atualização da lógica do game, em segundos

GLuint textureIndex1;
GLuint textureIndex2;

GLuint shaderID;
GLuint uniformTextUnit;
GLuint uniformMVPMatrix;

using namespace std;

string LoadFileToString(char * path)
{
	string file;
	ifstream myfile (path);
	if(myfile.is_open()){
		while(myfile.good()){
			getline (myfile,file);
    		}
		myfile.close();
	}else{
		 cout << "Unable to open file" << endl; 
	}
  	return file;
}
GLuint LoadTexture(const char * textureFileName, GLenum textureIndexUnit)
{
	GLuint texIndex = 0;
	GLint textureWidth;
	GLint textureHeight;
	GLint components;
	GLenum eFormat;
	GLbyte * textureData = gltReadTGABits(textureFileName, &textureWidth, &textureHeight, &components, &eFormat);

	glEnable(GL_TEXTURE_2D);
	
	glActiveTexture(textureIndexUnit);
	glGenTextures(1, &texIndex);
	glBindTexture(GL_TEXTURE_2D, texIndex);
	glTexImage2D(GL_TEXTURE_2D, 0, components, textureWidth, textureHeight, 0, eFormat, GL_UNSIGNED_BYTE, textureData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	

	free(textureData);
	return texIndex;
}

GLuint LoadShader(std::string vertexShaderStr, std::string fragmentShaderStr)
{
	GLuint programID;
	GLuint vertexShader;
	GLuint fragmentShader;

	GLint status;
	char log[1024];


	const char * vertexShaderChar = vertexShaderStr.c_str();
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

	const char * fragmentShaderChar = fragmentShaderStr.c_str();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderChar, NULL);
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
	uniformMVPMatrix = glGetUniformLocation(programID, "mvpMatrix");
	uniformTextUnit = glGetUniformLocation(programID, "textureUnit0");

	return programID;

}

/* KeyboardKeys */

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
			gCameraPosition[0] += cos(gCameraYaw) * 0.1f;
			gCameraPosition[2] += sin(gCameraYaw) * 0.1f;
			break;
		case GLUT_KEY_DOWN:
			gCameraPosition[0] -= cos(gCameraYaw) * 0.1f;
			gCameraPosition[2] -= sin(gCameraYaw) * 0.1f;
			break;
		case GLUT_KEY_LEFT:
			gCameraYaw -= 0.5f;
			break;
		case GLUT_KEY_RIGHT:
			gCameraYaw += 0.5f;
            break;
	}
}


/* GameRender */

void GameRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Limpa os buffers e deixa com a cor definida


    	shaderManager.UseStockShader(GLT_SHADER_SHADED, transformPipeline.GetModelViewProjectionMatrix());
    	linesBatch.Draw();
	axisBatch.Draw();
	

	glUseProgram(shaderID);
	glUniformMatrix4fv(uniformMVPMatrix, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());    
	glUniform1i(uniformTextUnit, 0);

	modelViewMatrix.PushMatrix();
    	modelViewMatrix.Translate(10, 2, 10);
    	shaderManager.UseStockShader(GLT_SHADER_SHADED, transformPipeline.GetModelViewProjectionMatrix());
    	sphereBatch.Draw();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textureIndex1);
	
	modelViewMatrix.PopMatrix();
    	glutSwapBuffers();
}

/*
void GameRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Limpa os buffers e deixa com a cor definida
    
    	// Desenha a cena
    	shaderManager.UseStockShader(GLT_SHADER_SHADED, transformPipeline.GetModelViewProjectionMatrix());
    	linesBatch.Draw();
	axisBatch.Draw();
    
    	// Translada e desenha a esfera
    	modelViewMatrix.Translate(10, 2, 10);
    	shaderManager.UseStockShader(GLT_SHADER_SHADED, transformPipeline.GetModelViewProjectionMatrix());
    	sphereBatch.Draw();

    	glutSwapBuffers();
}
*/

/* CameraSetup */

void ChangeSize(int w, int h) {
	if (h == 0) {
		h = 1;
	}
	glViewport(0, 0, w, h); // Configura a viewport de acordo com o tamanho da tela
	windowWidth = w;
	windowHeight = h;

    	viewFrustum.SetPerspective (45.0f, float(windowWidth)/float(windowHeight), 0.01f, 5000.f);
}

void CameraUpdate(void) {
    	projectionMatrix.LoadIdentity();
	projectionMatrix.LoadMatrix (viewFrustum.GetProjectionMatrix());
    
	M3DVector3f forwardVector = {0.0f, 0.0f, 0.0f};

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

/* GameLogic */

void GameLogic(void) {

}

/* MainCycle */

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


/* Init */

void Init() {
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f ); // Cor para limpar os buffers, e deixar como fundo da tela
	glEnable(GL_DEPTH_TEST); // Habilita o buffer de teste de profundidade
	glEnable(GL_CULL_FACE); // Habilita o culling de faces, por questoes de performance, desenhando apenas as faces da frente
    
    	// Inicializa o gerenciador de shaders
    	shaderManager.InitializeStockShaders();
   	textureIndex1 = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/data/texture/sun.tga", GL_TEXTURE0); 
   	textureIndex2 = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/data/texture/earth.tga", GL_TEXTURE1); 

	char * pathVShader = "/home/vanz/gitroot/VanzCoder/opengl/vertex.fsh";
	char * pathFShader = "/home/vanz/gitroot/VanzCoder/opengl/fragment.fsh";
	//std::string vertexShader = LoadFileToString(pathVShader);
	//std::string fragmentShader = LoadFileToString(pathFShader);
	//LoadShader(vertexShader, fragmentShader);

    	CreateBatch();
}

/* Main */

int main(int argc, char* argv[]){
	
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

/* CreateBatch */

void CreateBatch(){
    	// Cria uma esfera
	gltMakeSphere(sphereBatch, 1.0f, 26, 13);
    
    	// Cria os eixos
    	/* Initialise the axis batch with the vertices and color */
	axisBatch.Begin(GL_LINES, 6);
    
	// x Axis
	axisBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	axisBatch.Vertex3f(0.0f,0.0f,0.0f);
    	axisBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	axisBatch.Vertex3f(1.0f,0.0f,0.0f);
    
	// y Axis
    	axisBatch.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
	axisBatch.Vertex3f(0.0f,0.0f,0.0f);
    	axisBatch.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
	axisBatch.Vertex3f(0.0f,1.0f,0.0f);
    
	// z Axis
    	axisBatch.Color4f(0.0f, 0.0f, 1.0f, 1.0f);
	axisBatch.Vertex3f(0.0f,0.0f,0.0f);
    	axisBatch.Color4f(0.0f, 0.0f, 1.0f, 1.0f);
	axisBatch.Vertex3f(0.0f,0.0f,1.0f);
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
