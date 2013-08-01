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
	$(CC) $(CFLAGS) $(INCLUDE) -o curso $(TOOLSSRC)  CursoCG.cpp ObjFile.cpp $(LIBS)
triangulo:
	$(CC) $(CFLAGS) $(INCLUDE) -o triangulo $(TOOLSSRC)  triangle.cpp $(LIBS)
geotest:
	$(CC) $(CFLAGS) $(INCLUDE) -o geotest $(TOOLSSRC)  GeoTest.cpp $(LIBS)
blending:
	$(CC) $(CFLAGS) $(INCLUDE) -o blending $(TOOLSSRC)  Blending.cpp $(LIBS)
smoother:
	$(CC) $(CFLAGS) $(INCLUDE) -o smoother $(TOOLSSRC)  Smoother.cpp $(LIBS)
jogo:
	$(CC) $(CFLAGS) $(INCLUDE) -o jogo $(TOOLSSRC) jogo.cpp $(LIBS)

clean:
	rm curso
