#include "shape.hpp"

#include <GL/glew.h>

ogl::Shape::Shape(
   std::string_view vertex, 
   std::string_view fragment, 
   std::string_view texture)
   : Shader(vertex, fragment)
{


}
