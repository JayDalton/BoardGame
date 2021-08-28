#include "polyline.hpp"

#include <GL/glew.h>

/*#######################################################################
((V, N, C, T), (V, N, C, T), ...)
((vx,vy,vz, nx,ny,nz, cr,cg,cb, tx,ty), (...), ...)
#######################################################################*/
ogl::PolyLine::PolyLine(std::vector<glm::vec3> list, GLfloat r, GLfloat g, GLfloat b)
  : Shape()
{
  //Geometry::buffer_len = Geometry::struct_len * list.size();
  //Geometry::buffer = new GLfloat[Geometry::buffer_len];
  //for (unsigned int i = 0; i < list.size(); ++i) {
  //  buffer[struct_len * i + 0] = list[i].x;
  //  buffer[struct_len * i + 1] = list[i].y;
  //  buffer[struct_len * i + 2] = list[i].z;
  //  buffer[struct_len * i + 3] = list[i].x;
  //  buffer[struct_len * i + 4] = list[i].y;
  //  buffer[struct_len * i + 5] = list[i].z;
  //  buffer[struct_len * i + 6] = r;
  //  buffer[struct_len * i + 7] = g;
  //  buffer[struct_len * i + 8] = b;
  //  buffer[struct_len * i + 9] = 0.0f;
  //  buffer[struct_len * i +10] = 0.0f;
  //}

  //Geometry::indice_len = list.size();
  //indices = new GLuint[Geometry::indice_len];
  //for (unsigned int i = 0; i < indice_len; ++i) {
  //  indices[i] = i;
  //}
}

/*#######################################################################
#######################################################################*/
ogl::PolyLine::~PolyLine()
{
}

/*#######################################################################
#######################################################################*/
ogl::PolyLine::PolyLine(const PolyLine& original)
: Shape(original)
{
}

/*#######################################################################
#######################################################################*/
ogl::PolyLine& ogl::PolyLine::operator=(const PolyLine& original)
{
  if (this != &original) {
    Shape::operator=(original);
  }
  return *this;
}

/*#######################################################################
#######################################################################*/
void ogl::PolyLine::render() const
{
  //glEnableClientState(GL_VERTEX_ARRAY);
  //glEnableClientState(GL_NORMAL_ARRAY);
  //glEnableClientState(GL_COLOR_ARRAY);

  //glVertexPointer(3, GL_FLOAT, StructSize(), getBuffer());
  //glNormalPointer(GL_FLOAT, StructSize(), getBuffer(3));
  //glColorPointer(3, GL_FLOAT, StructSize(), getBuffer(6));
  //glDrawElements(GL_LINE_STRIP, IndiceLength(), GL_UNSIGNED_INT, getIndice());
  ////glDrawElements(GL_LINE_LOOP, IndiceLength(), GL_UNSIGNED_INT, getIndice());

  //glDisableClientState(GL_COLOR_ARRAY);
  //glDisableClientState(GL_NORMAL_ARRAY);
  //glDisableClientState(GL_VERTEX_ARRAY);
}
