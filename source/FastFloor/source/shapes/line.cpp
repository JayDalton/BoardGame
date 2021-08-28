#include "line.hpp"

#include <GL/glew.h>

ogl::Line::Line(glm::vec3 p1, glm::vec3 p2, GLfloat r, GLfloat g, GLfloat b)
  : Shape()
{
  Geometry::buffer_len = 2 * Geometry::struct_len;
  Geometry::buffer = new GLfloat[Geometry::buffer_len];

  buffer[0] = p1.x; buffer[1] = p1.y; buffer[2] = p1.z;
  buffer[3] = p1.x; buffer[4] = p1.y; buffer[5] = p1.z;
  buffer[6] = r; buffer[7] = g; buffer[8] = b;
  buffer[9] = 0.0f; buffer[10] = 0.0f;

  buffer[11] = p2.x; buffer[12] = p2.y; buffer[13] = p2.z;
  buffer[14] = p2.x; buffer[15] = p2.y; buffer[16] = p2.z;
  buffer[17] = r; buffer[18] = g; buffer[19] = b;
  buffer[20] = 0.0f; buffer[21] = 0.0f;

  Geometry::indice_len = 2;
  indices = new GLuint[Geometry::indice_len];
  for (unsigned int i = 0; i < indice_len; ++i) {
    indices[i] = i;
  }

}

/*###############################################################################
###############################################################################*/
ogl::Line::~Line()
{

}

/*#######################################################################
#######################################################################*/
ogl::Line::Line(const Line& original)
: Shape(original)
{
}

/*#######################################################################
#######################################################################*/
ogl::Line& ogl::Line::operator=(const Line& original)
{
  if (this != &original) {
    Shape::operator=(original);
  }
  return *this;
}

/*#######################################################################
#######################################################################*/
void ogl::Line::setP1(glm::vec3 p)
{
  buffer[0] = p.x;
  buffer[1] = p.y;
  buffer[2] = p.z;
}

/*#######################################################################
#######################################################################*/
glm::vec3 ogl::Line::getP1() const
{
  return glm::vec3(buffer[0], buffer[1], buffer[2]);
}

/*#######################################################################
#######################################################################*/
void ogl::Line::setP2(glm::vec3 p)
{
  buffer[11] = p.x;
  buffer[12] = p.y;
  buffer[13] = p.z;
}

/*#######################################################################
#######################################################################*/
glm::vec3 ogl::Line::getP2() const
{
  return glm::vec3(buffer[11], buffer[12], buffer[13]);
}

/*#######################################################################
#######################################################################*/
void ogl::Line::render() const
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_FLOAT, StructSize(), getBuffer());
  glNormalPointer(GL_FLOAT, StructSize(), getBuffer(3));
  glColorPointer(3, GL_FLOAT, StructSize(), getBuffer(6));
  glDrawElements(GL_LINE_STRIP, IndiceLength(), GL_UNSIGNED_INT, getIndice());

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}
