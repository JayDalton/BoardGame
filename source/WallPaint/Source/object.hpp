/*###############################################################################
  Kodierung: UTF-8 ohne BOM - ���
###############################################################################*/

#ifndef OGL_OBJECT_HPP
#define OGL_OBJECT_HPP

#include <SFML/OpenGL.hpp>

namespace ogl {

  class Object
  {
    private:
      static unsigned int id;

    public:
      Object();
      virtual ~Object();
      Object(const Object& shape);
      Object& operator=(const Object& shape);

  };
}

#endif