
#include <list>
#include <vector>
#include <glut.h>
#include <iostream>

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
	GLTriangleBatch batch;
	GLBatch batch2;
public:
	Obj(){};
	void addVertex(M3DVector3f v);
	void addVertex(GLfloat x, GLfloat y, GLfloat z);
	std::list<Vertex> getVertexes();
	void draw();
};
