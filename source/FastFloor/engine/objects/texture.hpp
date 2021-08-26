#pragma once

#include <SDL2/SDL_opengl.h>

#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>

#include "object.hpp"

namespace ogl {

  class Texture
  {
    public:
  	  GLuint id;

    private:
      GLuint compo;
  	  GLuint width;
  	  GLuint height;
  	  GLuint type;
  	  GLubyte* buffer;
      GLuint image_len;

    public:
      Texture(
        GLuint w, 
        GLuint h, 
        GLfloat cr = 1, 
        GLfloat cg = 1, 
        GLfloat cb = 1, 
        GLfloat ca = 1
      );

      Texture(
        GLuint w, 
        GLuint h, 
        GLuint type, 
        GLubyte* b
      );

      virtual ~Texture();

      void init();
      void bind();
      void free();

      void draw(
        GLint x, 
        GLint y, 
        const Texture* tex, 
        GLfloat cr = 0, 
        GLfloat cg = 0, 
        GLfloat cb = 0, 
        GLfloat ca = 0
      );

      void fill(
        GLfloat cr = 1, 
        GLfloat cg = 1, 
        GLfloat cb = 1, 
        GLfloat ra = 1
      );

  	  GLubyte* getBuffer() const;
      GLuint getBufferSize() const;
      GLuint getBufferLength() const;
  	  GLuint getSize() const;
  	  GLuint getWidth() const;
  	  GLuint getHeight() const;

      GLfloat getAlphaInfo() const;

  	  GLuint getType() const;
  	  GLuint getCompos() const;
  	  std::string getTypeName() const;
      std::string printDetail() const;

      Texture(const Texture& tex);
      Texture& operator=(const Texture& tex);

    private:
      GLubyte cv(GLfloat c) const;

  };

}
