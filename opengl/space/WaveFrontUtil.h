
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<stdio.h>
#include <boost/lexical_cast.hpp>


// GLTools
#include <GLTools.h>
#include <GLShaderManager.h> // Shader Manager Class
#include <GLFrustum.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <GLBatch.h>

#include <glut.h>


#include "Obj.h"

using boost::lexical_cast;

class WaveFrontUtil
{
public:

	static Obj* ReadObjFile(const char* path);
};
