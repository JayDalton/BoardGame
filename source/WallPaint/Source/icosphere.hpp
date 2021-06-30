/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_ICOSPHERE_HPP
#define OGL_ICOSPHERE_HPP

#include <map>
#include <vector>
#include <sstream>

#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shape.hpp"

namespace ogl {

  class IcoSphere : public Shape
  {
    private:
      GLuint Index;
      GLuint recursion;
      std::vector<glm::vec3> vertices;
      std::vector<glm::vec3> triangle;
      std::map<unsigned long, unsigned int> middlePointIndexCache;

    public:
      IcoSphere(
        unsigned int recursion = 2, 
        GLfloat cr = 1.0f, GLfloat cg = 1.0f, GLfloat cb = 1.0f
      );

      virtual ~IcoSphere();

      IcoSphere(const IcoSphere& ico);
      IcoSphere& operator=(const IcoSphere& ico);

      void render() const;
    
    private:
      void generate();
      void setBuffer();
      void setIndices();
      GLuint addVertex(glm::vec3 p);
      GLuint getMiddlePoint(GLuint p1, GLuint p2);

  };

}

#endif
