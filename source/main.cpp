#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include "loader.h"

using namespace std;

static GLuint texture;

static void clear()
{
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

static void update()
{

}

static void render()
{
    clear();

    int width;
    int height;

    texture = loadTexture("../res/ship.png", &width, &height);

    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glTexCoord2d(0.5f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glTexCoord2d(-0.5f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glTexCoord2d(-0.5f, -0.5f);
    glVertex2f(-0.5f, 0.5f);
    glTexCoord2d(0.5f, -0.5f);
    glEnd();

    glutSwapBuffers();
}

static int init(int* argc, char** argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(400, 300);
    glutCreateWindow("Hello, world!");
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glutDisplayFunc(&render);
    glutIdleFunc(&update);

    glewInit();
    if (!GLEW_VERSION_2_0)
    {
        fprintf(stderr, "OpenGL 2.0 not available\n");
        return 0;
    }

    return 0;
}

int main(int argc, char** argv)
{
    if(!init(&argc, argv))
    {
        return 1;
    }
    glutMainLoop();
    return 0;
}
