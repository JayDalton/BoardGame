#pragma once

#include <SDL2/SDL_opengl.h>

#include "object.hpp"
#include "geometry.hpp"
#include "transform.hpp"

namespace ogl {

  class Shape : public Object, public Geometry, public Transform // Animation
  {
    public:
      Shape();
      virtual ~Shape();
      Shape(const Shape& shape);
      Shape& operator=(const Shape& shape);

      virtual void render() const = 0;
      //virtual void update() const = 0;

  };
}

