
#include "ObjParserWavefront.h"

void ObjParserWavefront::parse(const char * arquivo, ObjFile* obj)
{

	std::string line;
	std::ifstream myfile(arquivo);
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
				obj->addVertice(x,y,z);
				//std::cout << "x = " << x << " | y = " << y << " | z = " << z << std::endl;
				//obj->Color4f(1.0f, 0.0f, 0.0f, 1.0f);
				//obj->Vertex3f(x,y,z);
			}else if(lineType == 1){ // coordenada texture
				float v = boost::lexical_cast<float>(strings[0]);
				float t = boost::lexical_cast<float>(strings[1]);
				//std::cout << "v = " << v << " | t = " << t << std::endl;
				//obj->MultiTexCoord2f(0,v,t);
			}else if(lineType == 2){ // normals
				float x = boost::lexical_cast<float>(strings[0]);
				float y = boost::lexical_cast<float>(strings[1]);
				float z = boost::lexical_cast<float>(strings[2]);
				//std::cout << "NORMAL -> x = " << x << " | y = " << y << " | z = " << z << std::endl;
				//obj->Normal3f(x,y,z);
			}else if(lineType == 3){ // face
				//std::cout << "FACES -> 1 = " << strings[0] << " | 2 = " << strings[1] << " | 3 = " << strings[2] << std::endl;
			}
			
		}
		std::cout << "Total de vertices = " << obj->getCountVertices()/3 << std::endl;
		
	}
}


void ObjFile::addVertice(float x, float y, float z)
{
	this->vertices.push_back(x);
	this->vertices.push_back(y);
	this->vertices.push_back(z);
}

int ObjFile::getCountVertices()
{
	return this->vertices.size();
}

GLfloat* ObjFile::getVerticeArray()
{
	GLfloat *array = new GLfloat[this->vertices.size()];
	for(int i = 0; i < this->vertices.size(); i++){
		array[i] = this->vertices.at(i);
	}
	return array;
}
