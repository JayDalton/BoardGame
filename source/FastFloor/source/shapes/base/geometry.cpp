#include "geometry.hpp"

#include <SDL2/SDL_opengl.h>

//############################################################################
/** 
((V, N, C, T), (V, N, C, T), ...)
((vx,vy,vz, nx,ny,nz, cr,cg,cb, tx,ty), (...), ...)
*/
//############################################################################  
ogl::Geometry::Geometry()
  : buffer(0), indices(0), buffer_len(0), indice_len(0), struct_len(11)
{
}

ogl::Geometry::~Geometry()
{
  delete indices;
  delete buffer;
}

ogl::Geometry::Geometry(const Geometry& original)
{
  buffer_len = original.buffer_len;
  indice_len = original.indice_len;
  struct_len = original.struct_len;

  buffer = new GLfloat[buffer_len];
  for (unsigned int i = 0; i < buffer_len; i++) {
    buffer[i] = original.buffer[i];
  }

  indices = new GLuint[indice_len];
  for (unsigned int i = 0; i < indice_len; i++) {
    indices[i] = original.indices[i];
  }
}

ogl::Geometry& ogl::Geometry::operator=(const Geometry& original)
{
  if(this != &original) {

    buffer_len = original.buffer_len;
    indice_len = original.indice_len;
    struct_len = original.struct_len;

    if (buffer) {delete buffer;}
    buffer = new GLfloat[buffer_len];
    for (unsigned int i = 0; i < buffer_len; i++) {
      buffer[i] = original.buffer[i];
    }

    if (indices) {delete indices;}
    indices = new GLuint[indice_len];
    for (unsigned int i = 0; i < indice_len; i++) {
      indices[i] = original.indices[i];
    }

  }
  return *this;
}

GLuint ogl::Geometry::BufferSize() const
{
  return sizeof(GLfloat) * buffer_len;
}

GLuint ogl::Geometry::BufferLength() const
{
  return buffer_len;
}

GLuint ogl::Geometry::StructSize() const
{
  return sizeof(GLfloat) * struct_len; //((vx,vy,vz)(nx,ny,nz)(cr,cg,cb)(tx,ty))
}

GLuint ogl::Geometry::StructLength() const
{
  return struct_len; //((vx,vy,vz)(nx,ny,nz)(cr,cg,cb)(tx,ty))
}

GLuint ogl::Geometry::IndiceSize() const
{
  return sizeof(GLuint) * indice_len;
}

GLuint ogl::Geometry::IndiceLength() const
{
  return indice_len;
}

GLfloat* ogl::Geometry::getBuffer(GLuint offset) const
{
  return buffer + offset;
}

GLuint* ogl::Geometry::getIndice(GLuint offset) const
{
  return indices + offset;
}

//############################################################################
/** 
((V, N, C, T), (V, N, C, T), ...)
((vx,vy,vz, nx,ny,nz, cr,cg,cb, tx,ty), (...), ...)
*/
//############################################################################  
void ogl::Geometry::setColor(GLfloat cr, GLfloat cg, GLfloat cb)
{
  unsigned int i = 0;
  GLfloat* q = buffer + buffer_len;
  for (GLfloat* p = buffer; p <= q; p++, i++) {

    if ((i + 5) % struct_len == 0) {
      *(p) = cr;
    }

    if ((i + 4) % struct_len == 0) {
      *(p) = cg;
    }

    if ((i + 3) % struct_len == 0) {
      *(p) = cb;
    }
  }
}

std::string ogl::Geometry::getIndiceString() const
{
  std::stringstream ss;
  if (0 != indices && 0 < indice_len) {
    ss << std::endl << "IndiceSize: " << indice_len << "_" << sizeof(GLuint) * indice_len;
    ss << std::endl << "Indices: ";
    for (unsigned int i = 0; i < indice_len; i += 3) {
      ss << *(indices + i + 0) << "," << *(indices + i + 1) << "," << *(indices + i + 2) << "," << " ";
    }
  }
  return ss.str();
}

std::string ogl::Geometry::getBufferString() const
{
  std::stringstream ss;
  ss.precision(4);
  if (0 != buffer && 0 < buffer_len) {
    ss << std::endl << "BufferSize: " << buffer_len << "_" << sizeof(GLfloat) * buffer_len;
    for (unsigned int i = 0; i < buffer_len; i += struct_len) {
      ss << std::endl << std::fixed
        << *(buffer + i + 0) << ","
        << *(buffer + i + 1) << ","
        << *(buffer + i + 2) << ","
        << " "
        << *(buffer + i + 3) << ","
        << *(buffer + i + 4) << ","
        << *(buffer + i + 5) << ","
        << " "
        << *(buffer + i + 6) << ","
        << *(buffer + i + 7) << ","
        << *(buffer + i + 8) << ","
        << " "
        << *(buffer + i + 9) << ","
        << *(buffer + i +10) << ""
        ;
    }
  }
  return ss.str();
}
