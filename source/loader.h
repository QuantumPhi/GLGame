#include <stdio.h>
#include <string.h>
#include <iostream>
#include <GL/gl.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <png.h>

#define TEXTURE_LOAD_ERROR 0

using namespace std;

static GLuint loadTexture(const char* file_name, int* width, int* height);
