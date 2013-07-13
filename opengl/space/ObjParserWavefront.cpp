
#include "ObjParserWavefront.h"

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
	// glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
 // 	glEnableClientState(GL_NORMAL_ARRAY);						// Enable normal arrays
	// glVertexPointer(3,GL_FLOAT,	0,Faces_Triangles);				// Vertex Pointer to triangle array
	// glNormalPointer(GL_FLOAT, 0, normals);						// Normal pointer to normal array
	// glDrawArrays(GL_TRIANGLES, 0, TotalConnectedTriangles);		// Draw the triangles
	// glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
	// glDisableClientState(GL_NORMAL_ARRAY);						// Disable normal arrays
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
