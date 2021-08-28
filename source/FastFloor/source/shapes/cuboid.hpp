#pragma once 

#include "shape.hpp"

namespace ogl {

  class Cuboid : public Shape
  {
    private:
      const static float VERTICES[][11];
      const static unsigned int INDICES[];
      float cuboid_u;
      float cuboid_v;
      float cuboid_w;

    public:
      Cuboid(
        float u = 1.0f, float v = 1.0f, float w = 1.0f,
        float r = 1.0f, float g = 1.0f, float b = 1.0f
      );
      virtual ~Cuboid();
      Cuboid(const Cuboid& cube);
      Cuboid& operator=(const Cuboid& cube);

      std::vector<glm::vec3> vertices() const;
      std::vector<std::vector<glm::vec3>> triangles() const;
      std::vector<std::vector<glm::vec3>> rectangles() const;
      std::vector<std::vector<float>> planeUVs() const;

      bool intersect(glm::vec3 p1, glm::vec3 p2, glm::vec3 &pI, unsigned int &plane) const;
      glm::vec3 center() const;

      void render() const override;
  };

}
