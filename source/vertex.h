class Vertex
{
public:
    Vertex(GLfloat** position, GLubyte** color);
protected:
    GLfloat** position;
    GLfloat** normal;
    GLubyte** color;
}
