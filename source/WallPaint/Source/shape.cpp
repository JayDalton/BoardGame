/*###############################################################################
Kodierung: UTF-8 ohne BOM - ���
###############################################################################*/

#include "shape.hpp"

//############################################################################
/** 
*/
//############################################################################  
ogl::Shape::Shape()
  : Object(), Geometry(), Transform()
{
}

//############################################################################
/** 
*/
//############################################################################  
ogl::Shape::~Shape()
{
}

//############################################################################
/** 
*/
//############################################################################  
ogl::Shape::Shape(const Shape& original)
  : Object(original), Geometry(original), Transform(original)
{
}

//############################################################################
/** 
*/
//############################################################################  
ogl::Shape& ogl::Shape::operator=(const Shape& original)
{
  if(this != &original) {
    Object::operator=(original);
    Geometry::operator=(original);
    Transform::operator=(original);
  }
  return *this;
}
