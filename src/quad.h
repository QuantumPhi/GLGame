#include <GL/gl.h>

class Quad
{
public:
    Quad(Vertex** _vertices)
    {
        vertices = _vertices
    }

    bindTexture(GLuint texture)
    {

    }
protected:
    Vertex** vertices;
}
