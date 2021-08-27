#pragma once

#include <memory>

//#include "base/buffer.hpp"
#include "base/geometry.hpp"
#include "base/shader.hpp"
#include "base/texture.hpp"
#include "base/transform.hpp"

namespace ogl 
{
   struct Ident
   {
      Ident() : m_id(counter++) { }

   private:
      unsigned int m_id{ 0 };
      inline static unsigned int counter{ 0 };
   };


  class Shape : public Ident, public Geometry, public Transform // Animation
  {
    public:
      Shape() = default;
      virtual ~Shape() = default;

      virtual void render() const = 0;
      //virtual void update() const = 0;
  };

  using ShapePtr = std::unique_ptr<Shape>;
}

