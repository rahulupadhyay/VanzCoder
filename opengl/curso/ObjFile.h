#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <vector>
#include <GLTools.h>
#include <GLTriangleBatch.h>

class ObjFile
{
private:
	GLBatch* batch;
	GLTriangleBatch tBatch;
	float rotationAngle;
public:
	ObjFile(const char * arquivo, int tipo);
	void Draw(void);
	void StartRotation(float rotationAngle, float x, float y, float z);
	void StopRotation(void);
	static void parse(const char * arquivo, GLBatch* batch);
};
