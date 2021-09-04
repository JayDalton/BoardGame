#pragma once 

#include "shape.hpp"

class Square : public ogl::Shape
{
public:
   ~Square() override;
   explicit Square(
      std::string_view vertex,
      std::string_view fragment,
      std::string_view texture);
   explicit Square(
      std::string_view vertex,
      std::string_view fragment);

   void bind() const override;
   void render() const override;

private:
   static constexpr std::array m_vertices {
      // positions          // colors           // texture coords
       0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
       0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // bottom right
      -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // bottom left
      -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f    // top left 
   };

   static constexpr std::array m_indices{
      0u, 1u, 3u,  // first triangle
      1u, 2u, 3u,  // second triangle
   };

   mutable unsigned int m_VBO{ 0 };
   mutable unsigned int m_VAO{ 0 };
   mutable unsigned int m_EBO{ 0 };
};

class Hexagon : public ogl::Shape
{
public:
   ~Hexagon();
   explicit Hexagon(
      std::string_view vertex,
      std::string_view fragment
   );

   void bind() const override;
   void render() const override;

private:
   //std::vector<float> m_vertices;
   static constexpr std::array m_vertices{
      // positions          // colors           // texture coords
       0.0f,  0.000f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
       1.0f,  0.000f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
       0.5f,  0.866f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
      -0.5f,  0.866f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
      -1.0f,  0.000f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left 
      -0.5f, -0.866f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left 
       0.5f, -0.866f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
   };

   //static constexpr std::array m_indices{
   //   1u, 0u, 2u,  // first triangle
   //   2u, 0u, 3u,  // second triangle
   //   3u, 0u, 4u,
   //   4u, 0u, 5u,
   //   5u, 0u, 6u,
   //   6u, 0u, 1u,
   //};
   static constexpr std::array m_indices{
      0u, 1u, 2u,  // first triangle
      0u, 2u, 3u,  // second triangle
      0u, 3u, 4u,
      0u, 4u, 5u,
      0u, 5u, 6u,
      0u, 6u, 1u,
   };

   mutable unsigned int m_VBO{ 0 };
   mutable unsigned int m_VAO{ 0 };
   mutable unsigned int m_EBO{ 0 };
};

class Rectangle : public ogl::Shape
{
public:
   explicit Rectangle(
      ogl::Size size, 
      ogl::Color color,
      std::string_view vertex,
      std::string_view fragment
   );

   explicit Rectangle(
      ogl::Size size, 
      std::string_view vertex,
      std::string_view fragment,
      std::string_view texture);

   ogl::Size getSize() const;
    
   void render() const override;

private:
   ogl::Size m_size;

   static constexpr std::array m_indices{ 0, 1, 3, 1, 2, 3 };

   static constexpr std::array m_vertices{
      // position       // normals        // colors         // texture
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
   };
};

