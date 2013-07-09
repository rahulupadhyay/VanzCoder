
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

void Obj::addVertex(Vertex v)
{
	this->vertexes.push_back(v);
}

std::list<Vertex> Obj::getVertexes()
{
	 return this->vertexes;
}
