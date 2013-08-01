#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <vector>
#include <GLTools.h>

class ObjFile
{
private:
	GLBatch* batch;

public:
	ObjFile(const char * arquivo);
	void Draw(void);
	static void parse(const char * arquivo, GLBatch* batch);
};
