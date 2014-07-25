#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

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

    glBegin(GL_QUADS);
    glColor4f(52.f/255, 152.f/255, 219.f/255, 0.5f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
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
    glutDisplayFunc(&render);
    glutIdleFunc(&update);

    glewInit();
    if (!GLEW_VERSION_2_0)
    {
        fprintf(stderr, "OpenGL 2.0 not available\n");
        return 1;
    }

    return 0;
}

int main(int argc, char** argv)
{
    if(init(&argc, argv))
    {
        return 1;
    }
    glutMainLoop();
    return 0;
}
