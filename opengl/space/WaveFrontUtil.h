
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


// GLTools
#include <GLTools.h>
#include <GLShaderManager.h>    // Shader Manager Class
#include <GLFrustum.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>

#include <glut.h>

class WaveFrontUtil
{
public:

	static void ReadObjFile(const char* path);
};
