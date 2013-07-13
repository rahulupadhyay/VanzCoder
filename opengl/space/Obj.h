
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
	std::list<float> vertexes;
	std::list<float> textureCoord;
	std::list<float> normal;
public:
	Obj(){};
	void addVertex(float x, float y, float z);
	void addTextureCoord(float s, float t);
	void addNormal(float x, float y, float z);
	std::list<float> getVertexes();
	std::list<float> getTextureCoord();
	std::list<float> getNormal();
	void draw();
};

