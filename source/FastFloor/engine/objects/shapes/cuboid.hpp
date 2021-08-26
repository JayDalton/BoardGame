#pragma once 

#include "../shape.hpp"

#include <SDL2/SDL_opengl.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace ogl {

  class Cuboid : public Shape
  {
    private:
      const static GLfloat VERTICES[][11];
      const static GLuint INDICES[];
      GLfloat cuboid_u;
      GLfloat cuboid_v;
      GLfloat cuboid_w;

    public:
      Cuboid(
        GLfloat u = 1.0f, GLfloat v = 1.0f, GLfloat w = 1.0f,
        GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f
      );
      virtual ~Cuboid();
      Cuboid(const Cuboid& cube);
      Cuboid& operator=(const Cuboid& cube);

      std::vector<glm::vec3> vertices() const;
      std::vector< std::vector<glm::vec3> > triangles() const;
      std::vector< std::vector<glm::vec3> > rectangles() const;
      std::vector< std::vector<GLfloat> > planeUVs() const;

      bool intersect(glm::vec3 p1, glm::vec3 p2, glm::vec3 &pI, GLuint &plane) const;
      glm::vec3 center() const;

      void render() const;

  };

}
