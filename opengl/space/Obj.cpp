
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

void Obj::addVertex(M3DVector3f v)
{
//	this->vertexes.push_back(v);
}

void Obj::addVertex(GLfloat x, GLfloat y, GLfloat z)
{
	batch2.Vertex3f(x,y,z);
}

std::list<Vertex> Obj::getVertexes()
{
	 return this->vertexes;
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
