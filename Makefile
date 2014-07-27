default_target: all

all:
	g++ source/* -o main -lGL -lGLU -lglut -lGLEW -lpng
