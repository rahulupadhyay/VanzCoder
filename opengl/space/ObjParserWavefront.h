#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <stdio.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <glut.h>

class ObjFile
{
private:
	std::vector<float> vertices;
	std::vector<float> textureCoord;
	std::vector<float> normal;
	std::vector<int> faces;
public:
	void addVertex(float x, float y, float z);
	void addTextureCoord(float s, float t);
	void addNormal(float x, float y, float z);
	void addFace(int fv1, int ftc1, int fn1, int fv2, int ftc2, int fn2, int fv3, int ftc3, int fn3);
	std::vector<float> getVertexes();
	std::vector<float> getTextureCoord();
	std::vector<float> getNormal();
	std::vector<int> getFaces();
	void draw();
	int getCountVertices();
	int getCountTextureCoord();
	int getCountNormals();
	int getCountFaces();
	GLfloat* getVerticeArray();

};

class ObjParserWavefront
{
public:
	void parse(const char * arquivo, ObjFile* obj);
};



