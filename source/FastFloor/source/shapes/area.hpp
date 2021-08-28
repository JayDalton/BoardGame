#pragma once

#include "rectangle.hpp"
#include "shape.hpp"

namespace ogl {

  class Area : public Rectangle, public Texture
  {
    public:
      Area(float au, float av, const Texture *tex);
      Area(float au, float av, const Texture &tex);
      Area(
         float au, float av,
        unsigned int tu = 10, unsigned int tv = 10,
        float cr = 1, float cg = 1,
        float cb = 1, float ca = 1
      );
      virtual ~Area();
      Area(const Area& area);
      Area& operator=(const Area& area);

      void setTexture(const Texture *tex);
      void setTexture(const Texture &tex);

      void draw(
        int x, 
        int y, 
        const Texture* tex, 
        float cr = 0, 
        float cg = 0, 
        float cb = 0, 
        float ca = 0
      );

      void fill(
        float cr = 1, 
        float cg = 1, 
        float cb = 1, 
        float ra = 1
      );

      void render() const override;
      bool strike(glm::vec3 p1, glm::vec3 p2, Texture *tex);

  };

}
