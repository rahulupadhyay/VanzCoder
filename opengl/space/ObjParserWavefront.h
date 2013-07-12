#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<stdio.h>
#include <boost/lexical_cast.hpp>
#include <glut.h>

class ObjFile
{
private:
	std::vector<float> vertices;

public:
	void addVertice(float x, float y, float z);
	int getCountVertices();
	GLfloat* getVerticeArray();

};

class ObjParserWavefront
{
public:
	void parse(const char * arquivo, ObjFile* obj);
};



