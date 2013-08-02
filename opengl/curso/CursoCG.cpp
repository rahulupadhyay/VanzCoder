//
//  CursoCG.cpp
//  CursoCG
//
//  Created by DBAPPZ on 13/05/13.
//  Copyright (c) 2013 Christian Hess. All rights reserved.
//

#include <time.h>
#include <iostream>
#include <stdlib.h>

// GLTools
#include <GLTools.h>
#include <GLShaderManager.h>    // Shader Manager Class
#include <GLFrustum.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>

#include <glut.h>

#include "ObjFile.h"

// Prototipos
void CreateBatch(void);
void parse(const char * arquivo, GLBatch* batch);
void desenhaAsteroides(void);
void criaEPosicionaAsteroides(void);
void movimentaRotacionaAsteroides(void);
void desenhaNave(void);
//Constantes
const int totalAsteroides = 10;

// Classes auxiliares do GLTools
GLShaderManager		shaderManager;     //The shader manager of GLTools
GLFrame				cameraFrame;       //Frame of reference for the camera
GLFrustum			viewFrustum;       //View frustum
GLMatrixStack		modelViewMatrix;   //Modelview Matrix
GLMatrixStack		projectionMatrix;  //Projection Matrix
GLGeometryTransform transformPipeline; //Geometry Transform Pipeline

// Parametros da camera
M3DVector3f			gCameraPosition =   {-5.0f, 1.0f, 0.0f};    //Camera position
M3DVector3f			gCameraLookAt =     {0.0f, 0.0f, 0.0f};     //Reference point to look at
M3DVector3f			gCameraUp =         {0.0f, 1.0f, 0.0f};	    //Camera up direction
GLfloat				gCameraYaw =        0.0f;					//Carmera Yaw

// Batchs
GLBatch				axisBatch;			// Batch de geometria dos eixos
GLBatch				linesBatch;			// Batch de geometria das linhas
GLTriangleBatch		sphereBatch;        // Batch de geometria da esfera
ObjFile*		asteroides[totalAsteroides];
ObjFile*		spaceshipBatch;

// Variaveis auxiliares
int                 windowWidth = 800;          // Largura da janela
int                 windowHeight = 600;         // Altura da janela
clock_t             lastClock = clock();        // Ticks do relógio
float               updateFrequency = 1.0;      // Frequencia de atualização da lógica do game, em segundos

//variaveis para controle da nave
float		posicaoNave[3] = {0.0f, 0.0f, 0.0f};
const float	fatorMovimentacaoNave = 0.090f;

//variaveis utilizadas para controlar movimentação dos asteroides
GLfloat 	posicaoAsteroides[totalAsteroides * 3];
float		anguloRotacaoAsteroid[totalAsteroides];

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
			//posicaoNave[0] += fatorMovimentacaoNave;
			gCameraPosition[0] += cos(gCameraYaw) * 0.1f;
			gCameraPosition[2] += sin(gCameraYaw) * 0.1f;
			break;
		case GLUT_KEY_DOWN:
			//posicaoNave[0] -= fatorMovimentacaoNave;
			gCameraPosition[0] -= cos(gCameraYaw) * 0.1f;
			gCameraPosition[2] -= sin(gCameraYaw) * 0.1f;
			break;
		case GLUT_KEY_LEFT:
			//posicaoNave[2] -= fatorMovimentacaoNave;
			gCameraYaw -= 0.5f;
			break;
		case GLUT_KEY_RIGHT:
			//posicaoNave[2] += fatorMovimentacaoNave;
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

	desenhaAsteroides();
   	desenhaNave(); 

	// Translada e desenha a esfera
	modelViewMatrix.PushMatrix();
    
	modelViewMatrix.Translate(10, 0, 10);
    
	glBindTexture(GL_TEXTURE_2D, texture1Index);
    
	// #MOD
	glUseProgram(shaderID);
	M3DMatrix44f *mvpMatrix = (M3DMatrix44f*)transformPipeline.GetModelViewProjectionMatrix();
	glUniformMatrix4fv(uniformMVPMatrix, 1, GL_FALSE, *mvpMatrix);
	glUniform1i(uniformTexUnit, 0);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE, transformPipeline.GetModelViewProjectionMatrix(), 0);
    
	sphereBatch.Draw();
    
	modelViewMatrix.PopMatrix();
    
	// Translada e desenha a esfera
	modelViewMatrix.PushMatrix();

	modelViewMatrix.Translate(5, 0, 5);
    
	glBindTexture(GL_TEXTURE_2D, texture2Index);	
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE, transformPipeline.GetModelViewProjectionMatrix(), 0);
	sphereBatch.Draw();
    
	modelViewMatrix.PopMatrix();
    
	glutSwapBuffers();
}

//função que desenha asteroides
void desenhaAsteroides()
{
	int contador = 0;
	float color[4] = {1.0f, 0.0f, 0.0f, 1.0f};    	
	while(contador < totalAsteroides){
		modelViewMatrix.PushMatrix();
		modelViewMatrix.Translate(posicaoAsteroides[contador*3], posicaoAsteroides[(contador*3)+1], posicaoAsteroides[(contador*3)+2]);
		modelViewMatrix.Rotate(anguloRotacaoAsteroid[contador], 0.0f, 1.0f, 0.0f);
    		shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), color);
		asteroides[contador]->Draw();
		modelViewMatrix.PopMatrix();
		contador++;
	}

}

void desenhaNave(void)
{
	float color[4] = {0.0f, 0.0f, 0.0f, 1.0f};    	
	glDisable(GL_CULL_FACE); // Habilita o culling de faces, por questoes de performance, desenhando apenas as faces da frente
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(posicaoNave[0], posicaoNave[1], posicaoNave[2]);
	modelViewMatrix.Rotate(-90.0f, 0.0f, 1.0f, 0.0f);
   	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), color);
	spaceshipBatch->Draw();
	modelViewMatrix.PopMatrix();
	glEnable(GL_CULL_FACE); // Habilita o culling de faces, por questoes de performance, desenhando apenas as faces da frente
	
}

GLuint LoadTexture(const char* textureFileName){
    GLuint textureIndex = 0;
    GLint textureWidth;
    GLint textureHeight;
    GLint components;
    GLenum eFormat;
    
    GLbyte *textureData = gltReadTGABits(textureFileName, &textureWidth, &textureHeight, &components, &eFormat);
    
    // Habilita as texturas 2D
    glEnable(GL_TEXTURE_2D);
    
    // Ativa a unidade de textura
    glActiveTexture(GL_TEXTURE0);
    
    // Gera um nome de textura
    glGenTextures(1, &textureIndex);
    
    // Vincula a textura no contexto atual
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    
    glTexImage2D(GL_TEXTURE_2D, 0, components, textureWidth, textureHeight, 0, eFormat, GL_UNSIGNED_BYTE, textureData);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Libera a textura
    free(textureData);
    
    return textureIndex;
}


// #MOD - 1
GLuint LoadShader(std::string vertexShaderStr, std::string fragmentShaderStr){
    GLuint programID;
    GLuint vertexShader;
    GLuint fragmentShader;
    
    //    GLint status;
    //    char log[1024];
    
    const char *vertexShaderChar = vertexShaderStr.c_str();
    
    // Cria o shader de vertice
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderChar, NULL);
    glCompileShader(vertexShader);
    
    //    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    //
    //    if(status == GL_FALSE){
    //        glGetShaderInfoLog(vertexShader, 1024, NULL, log);
    //        fprintf(stderr, "Vertex compile failed:\n%s\n", log);
    //        glDeleteShader(vertexShader);
    //        return 0;
    //    }
    
    const char *fragmenetShaderChar = fragmentShaderStr.c_str();
    
    // Cria o shader de fragmento
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmenetShaderChar, NULL);
    glCompileShader(fragmentShader);
    
    //    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    //
    //    if(status == GL_FALSE){
    //        glGetShaderInfoLog(fragmentShader, 1024, NULL, log);
    //        fprintf(stderr, "Fragment compile failed:\n%s\n", log);
    //        glDeleteShader(fragmentShader);
    //        return 0;
    //    }
    
    // Cria um programa principal
    programID = glCreateProgram();
    
    // Anexa os shaders no programa
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    
    // Atribui um "local" a um atributo
    glBindAttribLocation(programID, GLT_ATTRIBUTE_VERTEX, "vVertex");
    glBindAttribLocation(programID, GLT_ATTRIBUTE_TEXTURE0, "vTexCoord0");
    
    // Linka o programa
    glLinkProgram(programID);
    
    //    glGetProgramiv(programID, GL_LINK_STATUS, &status);
    //
    //    if(status == GL_FALSE){
    //      glGetProgramInfoLog(programID, 1024, NULL, log);
    //      fprintf(stderr, "Link failed:\n%s\n", log);
    //      glDeleteProgram(programID);
    //        return 0;
    //    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    glUseProgram(programID);
    
    // Busca pelas variaveis do shader
    uniformMVPMatrix = glGetUniformLocation(programID, "mvpMatrix");
    uniformTexUnit = glGetUniformLocation(programID, "textureUnit0");
    
    return programID;
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
	movimentaRotacionaAsteroides();
    
	CameraUpdate();
	GameRender();

}

void movimentaRotacionaAsteroides()
{
	int contador = 0;
	float anguloRotacao = 1.0f;
	while(contador < totalAsteroides){
		anguloRotacaoAsteroid[contador] += anguloRotacao;
		if(anguloRotacaoAsteroid[contador] >= 360){
			anguloRotacaoAsteroid[contador] = 0.0f;
		}
		//movimentacao aleatoria
		/*float fatorMovimentacao = 3.0f;
		srand(time(NULL));
		int eixo = rand() % 3;
		posicaoAsteroides[(contador*3)+eixo] += fatorMovimentacao;*/
		contador++;
	}
	
}

/* Init */
void Init() {
	glClearColor(0.3, 0.3, 0.3, 1.0);
	glEnable(GL_DEPTH_TEST); // Habilita o buffer de teste de profundidade
	glEnable(GL_CULL_FACE); // Habilita o culling de faces, por questoes de performance, desenhando apenas as faces da frente
    
    // Inicializa o gerenciador de shaders
    shaderManager.InitializeStockShaders();
    
    CreateBatch();
    
    // #MOD - add textureUnit
    texture1Index = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/curso/data/texture/sun.tga");
    texture2Index = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/curso/data/texture/earth.tga");
    
    std::string vertexShader = ReadFile("/home/vanz/gitroot/VanzCoder/opengl/curso/vertex.v2.vsh");
    std::string fragmentShader = ReadFile("/home/vanz/gitroot/VanzCoder/opengl/cursofragment.v2.fsh");
    
    shaderID = LoadShader(vertexShader, fragmentShader);
	
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

	criaEPosicionaAsteroides();	
	spaceshipBatch = new ObjFile("/home/vanz/gitroot/VanzCoder/opengl/curso/spaceship.obj", 2);
}
	
void criaEPosicionaAsteroides()
{
	int contador = 0;
	while(contador < totalAsteroides){
		asteroides[contador] = new ObjFile("/home/vanz/gitroot/VanzCoder/opengl/curso/asteroid.obj", 1);
		contador++;
	}
	posicaoAsteroides[0] = 0.0f; //x
	posicaoAsteroides[1] = 0.0f; //y
	posicaoAsteroides[2] = 50.0f;//z
	
	posicaoAsteroides[3] = 10.0f;
	posicaoAsteroides[4] = 0.0f;
	posicaoAsteroides[5] = 5.0f;

	posicaoAsteroides[6] = 20.0f;
	posicaoAsteroides[7] = 0.0f;
	posicaoAsteroides[8] = 15.0f;

	posicaoAsteroides[9] = 30.0f;
	posicaoAsteroides[10] = 0.0f;
	posicaoAsteroides[11] = 25.0f;

	posicaoAsteroides[12] = 15.0f;
	posicaoAsteroides[13] = 0.0f;
	posicaoAsteroides[14] = -10.0f;

	posicaoAsteroides[15] = 25.0f;
	posicaoAsteroides[16] = 0.0f;
	posicaoAsteroides[17] = -20.0f;

	posicaoAsteroides[18] = -15.0f;
	posicaoAsteroides[19] = 0.0f;
	posicaoAsteroides[20] = -15.0f;

	posicaoAsteroides[21] = -20.0f;
	posicaoAsteroides[22] = 0.0f;
	posicaoAsteroides[23] = -15.0f;

	posicaoAsteroides[24] = -15.0f;
	posicaoAsteroides[25] = 0.0f;
	posicaoAsteroides[26] = 5.0f;

	posicaoAsteroides[27] = -30.0f;
	posicaoAsteroides[28] = 0.0f;
	posicaoAsteroides[29] = 15.0f;
}

