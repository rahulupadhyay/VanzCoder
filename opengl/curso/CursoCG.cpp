//
//  CursoCG.cpp
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

#include <glut.h>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <vector>

void CreateBatch();
void parse(const char * arquivo, GLBatch* batch);

// Classes auxiliares do GLTools
GLShaderManager		shaderManager;     //The shader manager of GLTools
GLFrame				cameraFrame;       //Frame of reference for the camera
GLFrustum			viewFrustum;       //View frustum
GLMatrixStack		modelViewMatrix;   //Modelview Matrix
GLMatrixStack		projectionMatrix;  //Projection Matrix
GLGeometryTransform transformPipeline; //Geometry Transform Pipeline

// Parametros da camera
M3DVector3f			gCameraPosition =   {0.0f, 0.5f, 5.0f};    //Camera position
M3DVector3f			gCameraLookAt =     {0.0f, 0.0f, 0.0f};     //Reference point to look at
M3DVector3f			gCameraUp =         {0.0f, 1.0f, 0.0f};	    //Camera up direction
GLfloat				gCameraYaw =        0.0f;					//Carmera Yaw


// Batchs
GLBatch				axisBatch;			// Batch de geometria dos eixos
GLBatch				linesBatch;			// Batch de geometria das linhas
GLTriangleBatch		sphereBatch;        // Batch de geometria da esfera
GLBatch*				asteroidBatch;
GLBatch*		spaceshipBatch;

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
    	//asteroidBatch->Draw();
	spaceshipBatch->Draw();

    
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





# pragma mark GameLogic

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
    
    // #MOD - add textureUnit
    texture1Index = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/curso/data/texture/sun.tga");
    texture2Index = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/curso/data/texture/earth.tga");
    
    std::string vertexShader = ReadFile("/home/vanz/gitroot/VanzCoder/opengl/curso/vertex.v2.vsh");
    std::string fragmentShader = ReadFile("/home/vanz/gitroot/VanzCoder/opengl/cursofragment.v2.fsh");
    
    shaderID = LoadShader(vertexShader, fragmentShader);
	
    asteroidBatch = new GLBatch();
    parse("/home/vanz/gitroot/VanzCoder/opengl/curso/asteroid.obj", asteroidBatch);
	spaceshipBatch = new GLBatch();
   	parse("/home/vanz/gitroot/VanzCoder/opengl/curso/spaceship.obj", spaceshipBatch);
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

void parse(const char * arquivo, GLBatch* batch)
{
	std::cout << "Entrou no parse" << std::endl;
	std::string line;
	std::ifstream myfile(arquivo);
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texturas;
	std::vector<int> faces;
	if (myfile.is_open()){
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
			std::vector<std::string> stringsFace;
			std::size_t found = 0;
			std::size_t newFound = std::string::npos;
			while((newFound = line.find(' ', found)) != std::string::npos){
				strings.push_back(line.substr(found, newFound));
				line.erase(0,newFound+1);
				found = 0;
				newFound = std::string::npos;
			}
			strings.push_back(line.substr(found, newFound));
			if(lineType == 3){
				for(int i = 0; i < strings.size(); i++){
					std::vector<std::string> strs;
					boost::split(strs,strings.at(i),boost::is_any_of("/"));
					for(int i2 = 0; i2 < strs.size(); i2++){
						stringsFace.push_back(strs.at(i2));
					}
				}
			}

			/*----------------------------------------------------------*/
			if(lineType == 0){ // vertice
				float x = boost::lexical_cast<float>(strings[0]);
				float y = boost::lexical_cast<float>(strings[1]);
				float z = boost::lexical_cast<float>(strings[2]);
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}else if(lineType == 1){ // coordenada texture
				float v = boost::lexical_cast<float>(strings[0]);
				float t = boost::lexical_cast<float>(strings[1]);
				texturas.push_back(v);
				texturas.push_back(t);
			}else if(lineType == 2){ // normals
				float x = boost::lexical_cast<float>(strings[0]);
				float y = boost::lexical_cast<float>(strings[1]);
				float z = boost::lexical_cast<float>(strings[2]);
				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);
			}else if(lineType == 3){ // face
				int v1 = boost::lexical_cast<int>(stringsFace[0]);
				int tc1 = boost::lexical_cast<int>(stringsFace[1]);
				int n1 = boost::lexical_cast<int>(stringsFace[2]);

				int v2 = boost::lexical_cast<int>(stringsFace[3]);
				int tc2 = boost::lexical_cast<int>(stringsFace[4]);
				int n2 = boost::lexical_cast<int>(stringsFace[5]);

				int v3 = boost::lexical_cast<int>(stringsFace[6]);
				int tc3 = boost::lexical_cast<int>(stringsFace[7]);
				int n3 = boost::lexical_cast<int>(stringsFace[8]);
	
				faces.push_back(v1);
				faces.push_back(tc1);
				faces.push_back(n1);
				
				faces.push_back(v2);
				faces.push_back(tc2);
				faces.push_back(n2);
				
				faces.push_back(v3);
				faces.push_back(tc3);
				faces.push_back(n3);
			}
			
		}
		
	}
	int nVert = vertices.size()/3;
	std::cout << "Número de vertex " << nVert << std::endl;
	batch->Begin(GL_TRIANGLES,vertices.size());
	int count = 0;
	for(int i = 0; i < faces.size(); i += 9){
		int v1 = (faces.at(i)-1) * 3;	
		int v2 = (faces.at(i+3)-1) * 3;	
		int v3 = (faces.at(i+6)-1) * 3;	
		
		GLfloat x1 = vertices.at(v1);
		GLfloat y1 = vertices.at(v1+1);
		GLfloat z1 = vertices.at(v1+2);
		
		GLfloat x2 = vertices.at(v2);
		GLfloat y2 = vertices.at(v2+1);
		GLfloat z2 = vertices.at(v2+2);
		
		GLfloat x3 = vertices.at(v3);
		GLfloat y3 = vertices.at(v3+1);
		GLfloat z3 = vertices.at(v3+2);

		batch->Vertex3f(x1, y1, z1);
		batch->Vertex3f(x2, y2, z2);
		batch->Vertex3f(x3, y3, z3);
		count++;
	}
	batch->End(); 
	std::cout << "Total triangulo = " << count << std::endl;
}


