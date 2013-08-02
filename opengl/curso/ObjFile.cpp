#include "ObjFile.h"

ObjFile::ObjFile(const char * arquivo, int tipo)
{
	if(tipo == 1){ // asteroid ( esfera )
		gltMakeSphere(this->tBatch, 1.0f, 24 , 12);
	}else if (tipo == 2) { // nave ( cone ) 
		gltMakeCylinder(this->tBatch, 0.0f, 5.0f, 5.0f, 10, 10);
	}else{
		this->batch = new GLBatch;
		ObjFile::parse(arquivo, this->batch);
	}
}

void ObjFile::Draw(void)
{
	this->tBatch.Draw();
}
void ObjFile::StartRotation(float rotationAngle, float x, float y, float z)
{
	this->rotationAngle = rotationAngle;
}

void ObjFile::StopRotation(void)
{

}

void ObjFile::parse(const char * arquivo, GLBatch* batch)
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
	GLTriangleBatch tBatch;
	tBatch.BeginMesh(nVert);
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
		
		GLfloat nx1 = normals.at(v1);
		GLfloat ny1 = normals.at(v1+1);
		GLfloat nz1 = normals.at(v1+2);
		
		GLfloat nx2 = normals.at(v2);
		GLfloat ny2 = normals.at(v2+1);
		GLfloat nz2 = normals.at(v2+2);
		
		GLfloat nx3 = normals.at(v3);
		GLfloat ny3 = normals.at(v3+1);
		GLfloat nz3 = normals.at(v3+2);

		M3DVector3f verts[3] = {{x1,y1,z1},{x2,y2,z2},{x3,y3,z3}};
		M3DVector3f normals[3] = {{nx1,ny1,nz1},{nx2,ny2,nz2},{nx3,ny3,nz3}};
		M3DVector2f texture[3] = {{0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f}};
		
		tBatch.AddTriangle(verts,normals,texture);
		batch->Vertex3f(x1, y1, z1);
		batch->Vertex3f(x2, y2, z2);
		batch->Vertex3f(x3, y3, z3);
		count++;
	}
	tBatch.End();
	batch->End(); 
}





