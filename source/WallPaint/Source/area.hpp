/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_AREA_HPP
#define OGL_AREA_HPP

#include <SFML/OpenGL.hpp>

#include "rectangle.hpp"
#include "texture.hpp"

namespace ogl {

  class Area : public Rectangle, public Texture
  {
    public:
      Area(GLfloat au, GLfloat av, const Texture *tex);
      Area(GLfloat au, GLfloat av, const Texture &tex);
      Area(
        GLfloat au, GLfloat av,
        GLuint tu = 10, GLuint tv = 10,
        GLfloat cr = 1, GLfloat cg = 1,
        GLfloat cb = 1, GLfloat ca = 1
      );
      virtual ~Area();
      Area(const Area& area);
      Area& operator=(const Area& area);

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

      void render() const;
      bool strike(glm::vec3 p1, glm::vec3 p2, Texture *tex);

  };

}

#endif
