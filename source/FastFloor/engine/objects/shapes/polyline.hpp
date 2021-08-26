#pragma once 

#include "../shape.hpp"

#include <SDL2/SDL_opengl.h>

namespace ogl 
{
  class PolyLine : public Shape
  {
    public:
      PolyLine(
        std::vector<glm::vec3> list,
        GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f
        );
      virtual ~PolyLine();

      PolyLine(const PolyLine& poly);
      PolyLine& operator=(const PolyLine& poly);

      void add(glm::vec3);
      void add(std::vector<glm::vec3> lst);
      void rem(unsigned int idx);
      void set(unsigned int idx, glm::vec3);
      unsigned int size() const;

      void setColor(GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);

      void render() const override;

    private:
      std::vector<glm::vec3> plist;
  };
}

