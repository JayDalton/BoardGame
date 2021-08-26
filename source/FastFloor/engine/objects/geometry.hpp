#pragma once

#include <sstream>
#include <glm/glm.hpp>
#include <SDL2/SDL_opengl.h>

namespace ogl 
{
   class Geometry
   {
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

   protected:
      GLfloat* buffer;
      GLuint* indices;
      GLuint buffer_len;
      GLuint indice_len;
      GLuint struct_len;
   };
}
