/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_CUBE_HPP
#define OGL_CUBE_HPP

#include <SFML/OpenGL.hpp>

#include "cuboid.hpp"
#include "texture.hpp"

namespace ogl {

  class Cube : public Cuboid, public Texture
  {
    private:
      const Texture *fore;
      const Texture *back;

    public:
      Cube(
        GLfloat cu,
        GLfloat cv,
        GLfloat cw,
        GLuint tu,
        GLuint tv
      );
      ~Cube();
      Cube(const Cube& cube);
      Cube& operator=(const Cube& cube);

      void setForeTexture(const Texture *tex);
      void setBackTexture(const Texture *tex);

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
