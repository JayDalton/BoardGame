/*###############################################################################
Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_LINE_HPP
#define OGL_LINE_HPP

#include "shape.hpp"

namespace ogl {
  class Line : public Shape
  {
    public:
      Line(
        glm::vec3 p1, glm::vec3 p2, 
        GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f
      );
      virtual ~Line();

      Line(const Line& line);
      Line& operator=(const Line& line);

      void setP1(glm::vec3 p);
      glm::vec3 getP1() const;
      void setP2(glm::vec3 p);
      glm::vec3 getP2() const;

      void render() const;

    private:

  };
}

#endif