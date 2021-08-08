/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_BALL_HPP
#define OGL_BALL_HPP

#include <SFML/OpenGL.hpp>

#include "icosphere.hpp"
#include "texture.hpp"

namespace ogl {

  class Ball : public IcoSphere, public Texture
  {
    public:
      Ball(unsigned int recursion, const Texture *tex);
      Ball(unsigned int recursion, const Texture &tex);
      Ball(
        unsigned int recursion,
        GLuint tu = 10, GLuint tv = 10,
        GLfloat cr = 1, GLfloat cg = 1,
        GLfloat cb = 1, GLfloat ca = 1
      );
      virtual ~Ball();
      Ball(const Ball& area);
      Ball& operator=(const Ball& ball);

      void setTexture(const Texture *tex);
      void setTexture(const Texture &tex);

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

      bool strike(glm::vec3 p1, glm::vec3 p2, Texture *tex);

      void render() const;
  };

}

#endif
