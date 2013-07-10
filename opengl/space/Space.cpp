//
//  CursoCG.cpp
//  CursoCG
//
//  Created by DBAPPZ on 13/05/13.
//  Copyright (c) 2013 Christian Hess. All rights reserved.
//
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<stdio.h>

// GLTools
#include <GLTools.h>
#include <GLShaderManager.h>    // Shader Manager Class
#include <GLFrustum.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <boost/lexical_cast.hpp>

#include <glut.h>

void CreateBatch();
GLBatch* ReadObjFile(const char* path);

// Classes auxiliares do GLTools
GLShaderManager		shaderManager;     //The shader manager of GLTools
GLFrame			cameraFrame;       //Frame of reference for the camera
GLFrustum		viewFrustum;       //View frustum
GLMatrixStack		modelViewMatrix;   //Modelview Matrix
GLMatrixStack		projectionMatrix;  //Projection Matrix
GLGeometryTransform 	transformPipeline; //Geometry Transform Pipeline

// Parametros da camera
M3DVector3f		gCameraPosition =   {0.0f, 0.5f, 5.0f};    //Camera position
M3DVector3f		gCameraLookAt =     {0.0f, 0.0f, 0.0f};     //Reference point to look at
M3DVector3f		gCameraUp =         {0.0f, 1.0f, 0.0f};	    //Camera up direction
GLfloat			gCameraYaw =        0.0f;					//Carmera Yaw


// Batchs
GLBatch			axisBatch;			// Batch de geometria dos eixos
GLBatch			linesBatch;			// Batch de geometria das linhas
GLTriangleBatch		sphereBatch;        // Batch de geometria da esfera
GLBatch*			nave;

// Variaveis auxiliares
int                 windowWidth = 800;          // Largura da janela
int                 windowHeight = 600;         // Altura da janela
clock_t             lastClock = clock();        // Ticks do relógio
float               updateFrequency = 1.0;      // Frequencia de atualização da lógica do game, em segundos


// #MOD
GLuint texture1Index;
GLuint texture2Index;

// #MOD - 3
GLuint shaderID;
GLuint uniformTexUnit;
GLuint uniformMVPMatrix;

// #MOD
GLuint uniformTexUnit1;


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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa os buffers e deixa com a cor definida
	glViewport(0, 0, windowWidth, windowHeight); // Configura a viewport de acordo com o tamanho da tela
    
	// Desenha a cena
	shaderManager.UseStockShader(GLT_SHADER_SHADED, transformPipeline.GetModelViewProjectionMatrix());
	linesBatch.Draw();
	axisBatch.Draw();
	std::cout << "vai desenhar a nave" << std::endl;
//	sphereBatch.Draw();
	nave->Draw();    

    
	glutSwapBuffers();
}





# pragma mark GameLogic

GLuint LoadTexture(const char* textureFileName){
	return 0;
}


// #MOD - 1
GLuint LoadShader(std::string vertexShaderStr, std::string fragmentShaderStr){
	return 0;
}


// #MOD
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


/* CameraSetup */

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
	glClearColor(0.3, 0.3, 0.3, 1.0);
	glEnable(GL_DEPTH_TEST); // Habilita o buffer de teste de profundidade
	glEnable(GL_CULL_FACE); // Habilita o culling de faces, por questoes de performance, desenhando apenas as faces da frente
    
    // Inicializa o gerenciador de shaders
	shaderManager.InitializeStockShaders();
	CreateBatch();
	std::cout << "passou do createbatch" << std::endl;
	
    
    // #MOD - add textureUnit
   // texture1Index = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/curso/data/texture/sun.tga");
   // texture2Index = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/curso/data/texture/earth.tga");
    
  //  std::string vertexShader = ReadFile("/home/vanz/gitroot/VanzCoder/opengl/curso/vertex.v2.vsh");
   // std::string fragmentShader = ReadFile("/home/vanz/gitroot/VanzCoder/opengl/cursofragment.v2.fsh");
    
  //  shaderID = LoadShader(vertexShader, fragmentShader);
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
	
	//carrega nave

   	nave = ReadObjFile("/home/vanz/gitroot/VanzCoder/opengl/space/data/spaceship.obj"); 
   	std::cout << "nave carregada" << std::endl;
}

GLBatch* ReadObjFile(const char* path)
{

	std::string line;
	std::ifstream myfile(path);
	if (myfile.is_open()){
		GLBatch* obj = new GLBatch();
		obj->Begin(GL_TRIANGLES,49,2);
		while ( myfile.good() ){
			getline (myfile,line);
			int lineType = -1;
			if(line[0] == '#'){
				continue;
			}else if(line[0] == 'v' & line[1] == ' '){
				lineType = 0;
			}else if(line[0] == 'v' & line[1] == 't'){
				lineType = 1;
			}else if(line[0] == 'v' & line[1] == 'n'){
				lineType = 2;
			}else if(line[0] == 'f' & line[1] == ' '){
				lineType = 3;
			}
			line.erase(0,2);
			if(line[0] == ' '){
				line.erase(0,1);
			}
			if(line[line.length()-1] == ' '){
				line.erase(line.length() - 1, 1);
			}
			/*-----------------------------------------------------------
					Split string
			------------------------------------------------------------*/
			std::vector<std::string> strings;
			std::size_t found = 0;
			std::size_t newFound = std::string::npos;
			while((newFound = line.find(' ', found)) != std::string::npos){
				strings.push_back(line.substr(found, newFound));
				line.erase(0,newFound+1);
				found = 0;
				newFound = std::string::npos;
			}
				strings.push_back(line.substr(found, newFound));

			/*----------------------------------------------------------*/
			if(lineType == 0){ // vertice
				float x = boost::lexical_cast<float>(strings[0]);
				float y = boost::lexical_cast<float>(strings[1]);
				float z = boost::lexical_cast<float>(strings[2]);
				std::cout << "x = " << x << " | y = " << y << " | z = " << z << std::endl;
				obj->Color4f(1.0f, 0.0f, 0.0f, 1.0f);
				obj->Vertex3f(x,y,z);
			}else if(lineType == 1){ // coordenada texture
				float v = boost::lexical_cast<float>(strings[0]);
				float t = boost::lexical_cast<float>(strings[1]);
				std::cout << "v = " << v << " | t = " << t << std::endl;
				obj->MultiTexCoord2f(0,v,t);
			}else if(lineType == 2){ // normals
				float x = boost::lexical_cast<float>(strings[0]);
				float y = boost::lexical_cast<float>(strings[1]);
				float z = boost::lexical_cast<float>(strings[2]);
				std::cout << "NORMAL -> x = " << x << " | y = " << y << " | z = " << z << std::endl;
				obj->Normal3f(x,y,z);
			}else if(lineType == 3){ // face
				std::cout << "FACES -> 1 = " << strings[0] << " | 2 = " << strings[1] << " | 3 = " << strings[2] << std::endl;
			}
			
		}
		std::cout << " antes do end" << std::endl;
		obj->End();
		std::cout << "depois do end" << std::endl;
		return obj;
		
	}
}
