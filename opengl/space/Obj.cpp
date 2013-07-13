
#include "Obj.h"

GLfloat Vertex::GetX()
{
	return this->xAxis;
}

GLfloat Vertex::GetY()
{
	return this->yAxis;
}

GLfloat Vertex::GetZ()
{
	return this->zAxis;
}

std::vector<GLfloat> Vertex::GetAxis()
{
	std::vector<GLfloat> vs;
	vs.push_back(this->xAxis);
	vs.push_back(this->yAxis);
	vs.push_back(this->zAxis);
	return vs;
}

/*----------------------------------------------------------------
			OBJ CLASS
----------------------------------------------------------------*/

void Obj::addVertex(float x, float y, float z)
{
	this->vertexes.push_back(x);
	this->vertexes.push_back(y);
	this->vertexes.push_back(z);
}

void Obj::addTextureCoord(float s, float t)
{
	this->textureCoord.push_back(s);
	this->textureCoord.push_back(t);
}

void Obj::addNormal(float x, float y, float z)
{
	this->normal.push_back(x);
	this->normal.push_back(y);
	this->normal.push_back(z);
}

std::list<float> Obj::getVertexes()
{
	 return this->vertexes;
}

std::list<float> Obj::getTextureCoord()
{
	return this->textureCoord;
}

std::list<float> Obj::getNormal()
{
	return this->normal;
}

void Obj::draw()
{
//	std::cout << "Draw()" << std::endl;
//	glBegin(GL_TRIANGLE_STRIP);  
//	for (std::list<Vertex>::iterator it = this->vertexes.begin(); it != this->vertexes.end(); it++){
//		Vertex v = *it;
//		glColor3f(v.GetX(), v.GetY(), v.GetZ());
//	}
//	for (int i = 0; i < this->vertexes.size(); i++){
//		Vertex v = this->vertexes.at(i);
//		glColor3f(v.GetX(), v.GetY(), v.GetZ());
//	}
//	glEnd();
	
}
