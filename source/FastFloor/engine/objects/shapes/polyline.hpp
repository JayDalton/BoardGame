/*###############################################################################
Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_POLYLINE_HPP
#define OGL_POLYLINE_HPP

#include <vector>
#include "shape.hpp"

namespace ogl {
  class PolyLine : public Shape
  {
    public:
      PolyLine(
        std::vector<glm::vec3> list,
        GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f
        );
      virtual ~PolyLine();

      PolyLine(const PolyLine& poly);
      PolyLine& operator=(const PolyLine& poly);

      void add(glm::vec3);
      void add(std::vector<glm::vec3> lst);
      void rem(unsigned int idx);
      void set(unsigned int idx, glm::vec3);
      unsigned int size() const;

      void setColor(GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);

      void render() const;

    private:
      std::vector<glm::vec3> plist;
  };
}

#endif