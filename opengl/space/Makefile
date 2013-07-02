INCDIR = lib/GLTools/include/
INCPATH = lib/GLTools/src/
INCUTILS = utils/include
INCCOMMUM = commum/include
CC = g++
LIBS = -lglut -lGL -lGLU -lm
INCLUDE = -I$(INCDIR) -I$(INCDIR)GL -I$(INCUTILS) -I$(INCCOMMUM) -I/usr/include -I/usr/include/GL 
TOOLSSRC = $(INCPATH)GLTools.cpp $(INCPATH)GLShaderManager.cpp $(INCPATH)GLBatch.cpp $(INCPATH)glew.c $(INCPATH)GLTriangleBatch.cpp $(INCPATH)math3d.cpp
CFLAGS = -g

curso:
	$(CC) $(CFLAGS) $(INCLUDE) -o space $(TOOLSSRC) WaveFrontUtil.cpp Space.cpp $(LIBS)

clean:
	rm space
