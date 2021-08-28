#pragma once 

#include "shape.hpp"

class Rectangle : public ogl::Shape
{
public:
   explicit Rectangle(
      float u = 1.0f, float v = 1.0f, 
      float r = 1.0f, float g = 1.0f, float b = 1.0f
   );
   virtual ~Rectangle() = default;

   unsigned int getWidth() const;
   unsigned int getHeight() const;
   glm::vec3 getBase() const;

   std::vector<glm::vec3> vertices() const;
   bool intersect(glm::vec3 p1, glm::vec3 p2, glm::vec3 &pI) const;
    
   void render() const override;

private:
   const static float VERTICES[][11];
   const static unsigned INDICES[];
   //float rectangle_u;
   //float rectangle_v;
   static constexpr std::array m_indices{ 0, 1, 3, 1, 2, 3 };

   static constexpr std::array m_vertices{
      // position       // normals        // colors         // texture
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
   };

};

class Square : public ogl::Shape
{
public:
   explicit Square(
      std::string_view vertex,
      std::string_view fragment,
      std::string_view texture);

   void render() const override;

private:
   static constexpr std::array m_vertices {
      // positions          // colors           // texture coords
       0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
       0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
      -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
   };

   static constexpr std::array m_indices {
      0u, 1u, 3u,  // first triangle
      1u, 2u, 3u,  // second triangle
   };

   unsigned int m_VBO{ 0 };
   unsigned int m_VAO{ 0 };
   unsigned int m_EBO{ 0 };

   unsigned int m_texture{ 0 };
};

