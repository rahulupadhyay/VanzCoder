/*
* Author: José Guilherme Vanz <guilherme.sft@gmail.com>
*/

#include <time.h>
#include <iostream>

// GLTools
#include <GLTools.h>
#include <GLShaderManager.h>    // Shader Manager Class
#include <GLFrustum.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>

#include <glut.h>


// Classes auxiliares do GLTools
GLShaderManager		shaderManager;     //The shader manager of GLTools
GLFrame			cameraFrame;       //Frame of reference for the camera
GLFrustum		viewFrustum;       //View frustum
GLMatrixStack		modelViewMatrix;   //Modelview Matrix
GLMatrixStack		projectionMatrix;  //Projection Matrix
GLGeometryTransform 	transformPipeline; //Geometry Transform Pipeline

//Parametros de câmera
M3DVector3f	gCameraPosition = {0.0f, 0.5f, 5.0f};
M3DVector3f	gCameraLookAt   = {0.0f, 0.0f, 0.0f};
M3DVector3f	gCameraUp       = {0.0f, 1.0f, 0.0f};
GLfloat		gCameraYaw	= 0.0f;


// Windos dimensions
int windowWidth = 800;
int windowHeight = 600;

/* --- Prototipos --- */

void GameRender();  // Render scene
void GameLogic();   // Does the game login
void SpecialKeyboardAction(int key, int x, int y);  // Keyboard actions
void KeyboardAction(unsigned char key, int x, int y);  // Keyboard actions
void Init();  // init all stuff necessary before executation
void GameLoop(); // Execute the game loop
void CameraUpdate();
void ChangeSize(int width, int height);

/* ------------------- */


void GameRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa os buffers e deixa com a cor definida
	glViewport(0, 0, windowWidth, windowHeight); // Configura a viewport de acordo com o tamanho da tela

}

void GameLogic()
{

}

void SpecialKeyboardAction(int key, int x, int y)
{

}

void KeyboardAction(unsigned char key, int x, int y)
{

}

void GameLoop()
{

	CameraUpdate();
	GameRender();

	
}

void CameraUpdate()
{
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

void ChangeSize(int width, int height){
	windowWidth = width;
	windowHeight = height;
}

/*
 * Função que inicialização da aplicação
 */
void Init()
{
	glClearColor(0.3,0.3,0.3,1.0);
	glEnable(GL_DEPTH_TEST); // Habilita o buffer de teste de profundidade
	glEnable(GL_CULL_FACE); //Habilita o culling faces. Desse forma, somente as faces da frente são desenhadas.

//	shaderManager.InitializeStockShaders();

//	CreateBatch();

	//TODO - Carregar texturas

	//TODO - Carregar arquivos de shaders e carregar os shaders
	
}

/* Start here :) */
int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Space Vanz");

	GLenum err = glewInit();

	if(GLEW_OK != err){  
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;

	}

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(GameLoop);
	glutIdleFunc(GameLoop);
	glutSpecialFunc(SpecialKeyboardAction);
	glutKeyboardFunc(KeyboardAction);

	Init();

	glutMainLoop();
	return 0;	


}




