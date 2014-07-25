#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

static void update()
{

}

static void render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

static int init(int* argc, char** argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(400, 300);
    glutCreateWindow("Hello, world!");
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
