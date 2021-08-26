#pragma once 

#include <vector>
#include <sstream>

#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shape.hpp"

namespace ogl 
{

  class Rectangle : public Shape
  {
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
    
      void render() const override;

    private:
      const static GLfloat VERTICES[][11];
      const static GLuint INDICES[];
      //GLfloat rectangle_u;
      //GLfloat rectangle_v;

  };
}

