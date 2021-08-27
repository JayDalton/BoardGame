#pragma once 

#include "shape.hpp"

//#include <SDL2/SDL_opengl.h>

namespace ogl 
{
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

      void render() const override;

    private:

  };
}

