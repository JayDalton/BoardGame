/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_OBJMODEL_HPP
#define OGL_OBJMODEL_HPP

#include <vector>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shape.hpp"

namespace ogl {

  class ObjModel : public Shape
  {
    private:
      boost::filesystem::path path;

    public:
      ObjModel(
        boost::filesystem::path path,
        GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f
      );
      virtual ~ObjModel();

      ObjModel(const ObjModel& rect);
      ObjModel& operator=(const ObjModel& rect);
    
      virtual void render() const;

    private:
      GLvoid loadModel(
        std::ifstream& file, 
        GLfloat r, GLfloat g, GLfloat b
      );

  };
}

#endif
