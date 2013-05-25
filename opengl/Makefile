INCDIR = include/GLTools/include/
INCPATH = include/GLTools/src/
CC = g++
LIBS = -lglut -lGL -lGLU -lm
INCLUDE = -I$(INCDIR) -I$(INCDIR)GL -I/usr/include -I/usr/include/GL
TOOLSSRC = $(INCPATH)GLTools.cpp $(INCPATH)GLShaderManager.cpp $(INCPATH)GLBatch.cpp $(INCPATH)glew.c $(INCPATH)GLTriangleBatch.cpp $(INCPATH)math3d.cpp
CFLAGS =

triangle:
	$(CC) $(CFLAGS) $(INCLUDE) -o triangle $(TOOLSSRC)  triangle.cpp $(LIBS)
	

clean:
	
