/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_GEOMETRY_HPP
#define OGL_GEOMETRY_HPP

#include <sstream>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>

namespace ogl {

  class Geometry
  {
    protected:
      GLfloat* buffer;
      GLuint* indices;
      GLuint buffer_len;
      GLuint indice_len;
      GLuint struct_len;

    public:
      Geometry();
      virtual ~Geometry();
      Geometry(const Geometry& geom);
      Geometry& operator=(const Geometry& geom);

      GLfloat* getBuffer(GLuint offset = 0) const;
      GLuint* getIndice(GLuint offset = 0) const;
      GLuint StructSize() const;
      GLuint StructLength() const;
      GLuint BufferSize() const;
      GLuint BufferLength() const;
      GLuint IndiceSize() const;
      GLuint IndiceLength() const;

      std::string getIndiceString() const;
      std::string getBufferString() const;

      void setColor(GLfloat r, GLfloat g, GLfloat b);
  };
}

#endif