/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_2DTEXT_HPP
#define OGL_2DTEXT_HPP

#include <vector>
#include <iostream>

#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shape.hpp"
#include "texture.hpp"

namespace ogl {

  class TextLine2D : public Shape, public Texture
  {
    private:
      const static GLfloat VERTICES[][11];
      const static GLuint INDICES[];

    public:
      TextLine2D(
        std::string text, 
        const Texture *tex
      );
      virtual ~TextLine2D();

      TextLine2D(const TextLine2D& line);
      TextLine2D& operator=(const TextLine2D& line);

      virtual void render() const;
  };
}

#endif