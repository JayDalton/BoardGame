#pragma once

#include <memory>

#include <SDL2/SDL_opengl.h>

#include "object.hpp"
#include "geometry.hpp"
#include "transform.hpp"

namespace ogl {

  class Shape : public Object, public Geometry, public Transform // Animation
  {
    public:
      Shape();
      virtual ~Shape() = default;

      virtual void render() const = 0;
      //virtual void update() const = 0;
  };

  using ShapePtr = std::unique_ptr<Shape>;
}

