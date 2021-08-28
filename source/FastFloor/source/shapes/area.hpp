#pragma once

#include "rectangle.hpp"
#include "shape.hpp"

namespace ogl {

  class Area : public Rectangle, public Texture
  {
    public:
      Area(
         float au, float av,
         unsigned int tu = 10, 
         unsigned int tv = 10,
         Color color = {}
      );
      ~Area() override = default;

      void draw(
        int x, 
        int y, 
        const Texture* tex, 
        float cr = 0, 
        float cg = 0, 
        float cb = 0, 
        float ca = 0
      );

      void fill(Color color);

      void render() const override;
      bool strike(glm::vec3 p1, glm::vec3 p2, Texture *tex);

  };

}
