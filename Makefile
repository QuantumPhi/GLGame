default_target: all

all:
	gcc source/* -o main -lGL -lGLU -lglut -lGLEW -lpng
