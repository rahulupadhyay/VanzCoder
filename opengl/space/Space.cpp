#ifndef __SPACE_H__
#define __SPACE_H__


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
#include <boost/algorithm/string.hpp>

#include <glut.h>
//#include "ObjParserWavefront.h"

//----------------------------------------------------------------
class ObjFile
{
private:
	std::vector<float> vertices;
	std::vector<float> textureCoord;
	std::vector<float> normal;
	std::vector<int> faces;
	GLBatch batch;        // Batch do obj
public:
	void addVertex(float x, float y, float z);
	void addTextureCoord(float s, float t);
	void addNormal(float x, float y, float z);
	void addFace(int fv1, int ftc1, int fn1, int fv2, int ftc2, int fn2, int fv3, int ftc3, int fn3);
	std::vector<float> getVertexes();
	std::vector<float> getTextureCoord();
	std::vector<float> getNormal();
	std::vector<int> getFaces();
	void draw();
	int getCountVertices();
	int getCountTextureCoord();
	int getCountNormals();
	int getCountFaces();
	GLfloat* getVerticeArray();
	void ready();

};

class ObjParserWavefront
{
public:
	void parse(const char * arquivo, ObjFile* obj);
};


void ObjParserWavefront::parse(const char * arquivo, ObjFile* obj)
{

	std::string line;
	std::ifstream myfile(arquivo);
	int totalVertice = 0;
	int totalTextura = 0;
	int totalNormal = 0;
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
				obj->addVertex(x,y,z);
			}else if(lineType == 1){ // coordenada texture
				float v = boost::lexical_cast<float>(strings[0]);
				float t = boost::lexical_cast<float>(strings[1]);
				obj->addTextureCoord(v,t);
			}else if(lineType == 2){ // normals
				float x = boost::lexical_cast<float>(strings[0]);
				float y = boost::lexical_cast<float>(strings[1]);
				float z = boost::lexical_cast<float>(strings[2]);
				obj->addNormal(x,y,z);
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
				obj->addFace(v1,tc1,n1,v2,tc2,n2,v3,tc3,n3);
			}
			
		}
		std::cout << "Total de vertices = " << obj->getCountVertices() << std::endl;
		std::cout << "Total de texture coord = " << obj->getCountTextureCoord() << std::endl;
		std::cout << "Total de normal = " << obj->getCountNormals() << std::endl;
		std::cout << "Total de faces = " << obj->getCountFaces() << std::endl;
		obj->ready();

		
	}
}


void ObjFile::addVertex(float x, float y, float z)
{
	this->vertices.push_back(x);
	this->vertices.push_back(y);
	this->vertices.push_back(z);
}

void ObjFile::addTextureCoord(float s, float t)
{
	this->textureCoord.push_back(s);
	this->textureCoord.push_back(t);
}

void ObjFile::addNormal(float x, float y, float z)
{
	this->normal.push_back(x);
	this->normal.push_back(y);
	this->normal.push_back(z);
}

void ObjFile::addFace(int fv1, int ftc1, int fn1, int fv2, int ftc2, int fn2, int fv3, int ftc3, int fn3)
{
	this->faces.push_back(fv1);
	this->faces.push_back(ftc1);
	this->faces.push_back(fn1);

	this->faces.push_back(fv2);
	this->faces.push_back(ftc2);
	this->faces.push_back(fn2);

	this->faces.push_back(fv3);
	this->faces.push_back(ftc3);
	this->faces.push_back(fn3);
}

std::vector<int> ObjFile::getFaces()
{
	return this->faces;
}

std::vector<float> ObjFile::getVertexes()
{
	 return this->vertices;
}

std::vector<float> ObjFile::getTextureCoord()
{
	return this->textureCoord;
}

std::vector<float> ObjFile::getNormal()
{
	return this->normal;
}

void ObjFile::draw()
{
	//TODO
	this->batch.Draw();
}

int ObjFile::getCountFaces()
{
	std::cout << "Total de elementos de face = " << this->faces.size() << std::endl;
	return this->faces.size()/9;
}

int ObjFile::getCountVertices()
{
	return this->vertices.size()/3;
}

int ObjFile::getCountTextureCoord()
{
	return this->textureCoord.size()/2;
}

int ObjFile::getCountNormals()
{
	return this->normal.size()/3;
}

GLfloat* ObjFile::getVerticeArray()
{
	GLfloat *array = new GLfloat[this->vertices.size()];
	for(int i = 0; i < this->vertices.size(); i++){
		array[i] = this->vertices.at(i);
	}
	return array;
}
	
void ObjFile::ready()
{
	this->batch.Begin(GL_QUADS, this->getCountVertices(), 1);
	for(int i = 0; i < this->vertices.size(); i = i+3){
		this->batch.Color4f(i*4.0,i*2.0,i*0.1,1.0f);
        	this->batch.Vertex3f(this->vertices.at(i), this->vertices.at(i+1), this->vertices.at(i+2));
		//this->batch.Normal3f(this->normal.at(i), this->normal.at(i+1), this->normal.at(i+2));
	}
	this->batch.End();
	
	
}


//----------------------------------------------------------------



void CreateBatch();
// Classes auxiliares do GLTools
GLShaderManager		shaderManager;     //The shader manager of GLTools
GLFrame				cameraFrame;       //Frame of reference for the camera
GLFrustum			viewFrustum;       //View frustum
GLMatrixStack		modelViewMatrix;   //Modelview Matrix
GLMatrixStack		projectionMatrix;  //Projection Matrix
GLGeometryTransform transformPipeline; //Geometry Transform Pipeline

// Parametros da camera
M3DVector3f			gCameraPosition =   {-10.0f, 0.5f, 0.0f};    //Camera position
M3DVector3f			gCameraLookAt =     {5.0f, 5.0f, 5.0f};     //Reference point to look at
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
//ObjModel                *model = new ObjModel();
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

ObjFile* objNave;
GLfloat moveNaveX = 0, moveNaveY = 0, moveNaveZ = 0;

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
			//gCameraPosition[0] += cos(gCameraYaw) * 0.1f;
			//gCameraPosition[2] += sin(gCameraYaw) * 0.1f;
			moveNaveZ+=10;
			break;
		case GLUT_KEY_DOWN:
		//	gCameraPosition[0] -= cos(gCameraYaw) * 0.1f;
		//	gCameraPosition[2] -= sin(gCameraYaw) * 0.1f;
			moveNaveZ-10;
			break;
		case GLUT_KEY_LEFT:
		//	gCameraYaw -= 0.5f;
			moveNaveX-10;
			break;
		case GLUT_KEY_RIGHT:
		//	gCameraYaw += 0.5f;
			moveNaveX+10;
            break;
	}
}


/* GameRender */

void GameRender(void) {
	 glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, windowWidth, windowHeight);
    
    shaderManager.UseStockShader(GLT_SHADER_SHADED, transformPipeline.GetModelViewProjectionMatrix());
    linesBatch.Draw();
	axisBatch.Draw();

  	glPushMatrix();

        glTranslatef(moveNaveX, moveNaveY, moveNaveZ);
	glutSolidCube(0.5);

        glPopMatrix();

 
	
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
	glEnable(GL_DEPTH_TEST); // Habilita o buffer de teste de profundidade
	//glEnable(GL_CULL_FACE); // Habilita o culling de faces, por questoes de performance, desenhando apenas as faces da frente
    
    // Inicializa o gerenciador de shaders
    shaderManager.InitializeStockShaders();
    
    textureIndex1 = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/space/data/texture/sun.tga", GL_TEXTURE0);
    textureIndex2 = LoadTexture("/home/vanz/gitroot/VanzCoder/opengl/space/data/texture/earth.tga", GL_TEXTURE1);
    
    std::string vertexShader = ReadFile("/home/vanz/gitroot/VanzCoder/opengl/space/vertex.v1.vsh");
    std::string fragmentShader = ReadFile("/home/vanz/gitroot/VanzCoder/opengl/space/fragment.v1.fsh");
    
    shaderID = LoadShader(vertexShader, fragmentShader);
    
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
	
	//carrega nave
	ObjParserWavefront parser;
	objNave = new ObjFile();
  	//parser.parse("/vanz/home/gitroot/VanzCoder/opengl/space/data/asteroid.obj", objNave); 

	//FRENTE
	objNave->addVertex(5,0,0);
	objNave->addVertex(5,5,0);
	objNave->addVertex(10,0,0);
	objNave->addVertex(10,5,0);

	//LATERAR ESQUERDA
	objNave->addVertex(5,0,0);
	objNave->addVertex(5,0,5);
	objNave->addVertex(5,5,5);
	objNave->addVertex(5,5,0);

	//SUPERIOR
	objNave->addVertex(5,5,0);
	objNave->addVertex(5,5,5);
	objNave->addVertex(10,5,5);
	objNave->addVertex(10,5,0);

	//ATRAS
	objNave->addVertex(5,5,5);
	objNave->addVertex(10,5,5);
	objNave->addVertex(10,0,5);
	objNave->addVertex(5,0,5);

	//LATERAR DIREITA
	objNave->addVertex(10,5,0);
	objNave->addVertex(10,5,5);
	objNave->addVertex(10,0,5);
	objNave->addVertex(10,0,0);

	//BAIXO
	objNave->addVertex(5,0,0);
	objNave->addVertex(5,0,5);
	objNave->addVertex(10,0,5);
	objNave->addVertex(10,0,0);

	objNave->ready();

	
}


#endif
