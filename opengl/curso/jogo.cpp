#include <GLTools.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <GLFrustum.h>
#include <GLFrame.h>
#include <GLShaderManager.h>    // Shader Manager Class

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <vector>
/*-----------prototipo----------------*/
void MainCycle(void);
void CameraUpdate(void);
void SpecialKeys(int key, int x, int y);
void KeyboardFunc(unsigned char key, int x, int y);
void parse(const char * arquivo, GLBatch* batch);
/*------------------------------------*/

/*------------ Parametros da camera-----------*/
M3DVector3f			gCameraPosition =   {0.0f, 0.5f, 5.0f};    //Camera position
M3DVector3f			gCameraLookAt =     {0.0f, 0.0f, 0.0f};     //Reference point to look at
M3DVector3f			gCameraUp =         {0.0f, 1.0f, 0.0f};	    //Camera up direction
GLfloat				gCameraYaw =        0.0f;					//Carmera Yaw
/*-------------------------------------*/

// Classes auxiliares do GLTools
GLFrame				cameraFrame;       //Frame of reference for the camera
GLFrustum			viewFrustum;       //View frustum
GLMatrixStack		modelViewMatrix;   //Modelview Matrix
GLMatrixStack		projectionMatrix;  //Projection Matrix
GLGeometryTransform transformPipeline; //Geometry Transform Pipeline
GLShaderManager shaderManager;

/*------------------- Batches ----------------*/
GLBatch triangleBatch;
GLBatch * asteroidBatch;
/*--------------------------------------------*/
void ChangeSize(int w, int h)
{
	glViewport(0,0,w,h);
}

void KeyboardFunc(unsigned char key, int x, int y) 
{
    
	switch(key) {
		case 'a':
			break;
		case 'w':
			break;
		case 's':
			break;
	}
}

void SpecialKeys(int key, int x, int y) 
{
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

void SetupRC()
{
	//Blue background
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	shaderManager.InitializeStockShaders();

	//Load up triangle
	GLfloat vVerts[] = {-0.5f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f};

	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();

	asteroidBatch = new GLBatch();
	parse("/home/vanz/gitroot/VanzCoder/opengl/curso/asteroid.obj", asteroidBatch);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	//triangleBatch.Draw();

	glutSwapBuffers();
}

void CameraUpdate(void) 
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


void MainCycle(void){
	CameraUpdate();
	RenderScene();
}

int main(int argc, char * argv[])
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800,600);
	glutCreateWindow("Triangle");
	glutReshapeFunc(ChangeSize);
   	glutDisplayFunc(MainCycle);
	glutIdleFunc(MainCycle);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(KeyboardFunc);

	GLenum err = glewInit();
	if(GLEW_OK != err){
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	SetupRC();
	glutMainLoop();
	return 0;

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


