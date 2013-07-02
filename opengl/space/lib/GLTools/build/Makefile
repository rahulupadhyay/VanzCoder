# Compile and create a .so for GLTools
# Author: José Guilherme Vanz < guilherme.sft@gmail.com >

CC = g++# Compiler
WFLAGS = -fPIC -Wall -c # Waring flags
CCFLAGS = $(WFLAGS)# All compiler flags 
INCDIR = ../include/# Include directory for src 
INCLUDE = -I$(INCDIR) -I$(INCDIR)/GL# All includes directory
SRCPATH = ../src/# src directory
LIBS = -lglut -lGL -lGLU -lm# libs used
FILES = $(SRCPATH)GLBatch.cpp $(SRCPATH)glew.c $(SRCPATH)GLShaderManager.cpp $(SRCPATH)GLTools.cpp $(SRCPATH)GLTriangleBatch.cpp $(SRCPATH)math3d.cpp # Files sources
OFILES = GLBatch.o glew.o GLShaderManager.o GLTools.o GLTriangleBatch.o math3d.o
SONAME = libgltools.so

compile:
	$(CC) $(CCFLAGS) $(INCLUDE) $(FILES) $(LIBS)
so:
	$(CC) -shared -o $(SONAME) $(OFILES)
	cp $(SONAME) ../../bin
clean:
	rm $(OFILES) $(SONAME) 
