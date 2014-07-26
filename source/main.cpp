#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include "loader.cpp"

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

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2d(0.f, 0.f);
    glVertex2f(-0.5f, -0.5f);
    glTexCoord2d(1.f, 0.f);
    glVertex2f(0.5f, -0.5f);
    glTexCoord2d(1.f, 1.f);
    glVertex2f(0.5f, 0.5f);
    glTexCoord2d(0.f, 1.f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

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
    glutDisplayFunc(&render);
    glutIdleFunc(&update);

    glewInit();
    if (!GLEW_VERSION_2_0)
    {
        return 0;
    }

    texture = loadTexture("ship.png", NULL, NULL);

    return 1;
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
