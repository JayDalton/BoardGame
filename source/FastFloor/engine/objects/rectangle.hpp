/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_RECTANGLE_HPP
#define OGL_RECTANGLE_HPP

#include <vector>
#include <sstream>

#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shape.hpp"

namespace ogl {

  class Rectangle : public Shape
  {
    private:
      const static GLfloat VERTICES[][11];
      const static GLuint INDICES[];
      //GLfloat rectangle_u;
      //GLfloat rectangle_v;

    public:
      Rectangle(
        GLfloat u = 1.0f, GLfloat v = 1.0f, 
        GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f
      );
      virtual ~Rectangle();

      Rectangle(const Rectangle& rect);
      Rectangle& operator=(const Rectangle& rect);

      GLuint getWidth() const;
      GLuint getHeight() const;
      glm::vec3 getBase() const;

      std::vector<glm::vec3> vertices() const;
      bool intersect(glm::vec3 p1, glm::vec3 p2, glm::vec3 &pI) const;
    
      virtual void render() const;

  };
}

#endif
