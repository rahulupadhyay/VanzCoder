
#include <list>
#include <vector>
#include <glut.h>

class Vertex
{
private:
	GLfloat xAxis;
	GLfloat yAxis;
	GLfloat zAxis;

public:
	Vertex(GLfloat x, GLfloat y, GLfloat z): xAxis(x), yAxis(y), zAxis(z){};
	GLfloat GetX();
	GLfloat GetY();
	GLfloat GetZ();
	std::vector<GLfloat> GetAxis();
};


class Obj
{
private:
	std::list<Vertex> vertexes;

public:
	Obj(){};
	void addVertex(Vertex v);
	std::list<Vertex> getVertexes();
};
