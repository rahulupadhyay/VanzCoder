# Compile and create a .so for GLTools
# Author: José Guilherme Vanz < guilherme.sft@gmail.com >

CC = g++# Compiler
WFLAGS = -Wall# Waring flags
CCFLAGS = $(WFLAGS)# All compiler flags 
INCDIR = include/# Include directory for src 
INCLUDE = -I$(INCDIR)# All includes directory
SRCPATH = src/# src directory
LIBS = -lglut -lGL -lGLU -lm# libs used
FILES = $(SRCPATH)GLBatch.cpp $(SRCPATH)glew.c $(SRCPATH)GLShaderManager.cpp $(SRCPATH)GLTools.cpp $(SRCPATH)GLTriangleBatch.cpp $(SRCPATH)math3d.cpp# Files sources

so:
	$(CC) $(CCFLAGS) $(INCLUDE) $(FILES) $(LIBS)
