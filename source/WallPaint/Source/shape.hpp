/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_SHAPE_HPP
#define OGL_SHAPE_HPP

#include <SFML/OpenGL.hpp>

#include "object.hpp"
#include "geometry.hpp"
#include "transform.hpp"

namespace ogl {

  class Shape : public Object, public Geometry, public Transform
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

#endif