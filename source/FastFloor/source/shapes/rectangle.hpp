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
      std::string_view fragment,
      ogl::Color color);

   //void bind() const override;
   void render() const override;

private:
   //ObjectList<4> m_vertices;
   ////std::array<Element, 4> m_vertices;
   //static constexpr std::array m_indices{
   //   0u, 1u, 3u,  // first triangle
   //   1u, 2u, 3u,  // second triangle
   //};
};

class Rectangle : public ogl::Shape
{
public:
   ~Rectangle() override;
   explicit Rectangle(
      ogl::SizeF size, 
      std::string_view vertex,
      std::string_view fragment,
      ogl::Color color
   );

   explicit Rectangle(
      ogl::SizeF size, 
      std::string_view vertex,
      std::string_view fragment,
      std::string_view texture);

   ogl::Size getSize() const;
    
   //void bind() const override;
   void render() const override;

private:
   ogl::Size m_size;
   //std::array<Element, 4> m_vertices{};
   //static constexpr std::array m_indices{
   //   0u, 1u, 3u,  // first triangle
   //   1u, 2u, 3u,  // second triangle
   //};

};

class Hexagon : public ogl::Shape
{
public:
   ~Hexagon();
   explicit Hexagon(
      std::string_view vertex,
      std::string_view fragment,
      ogl::Color color
   );

   //void bind() const override;
   void render() const override;

private:
   //std::array<Element, 7> m_vertices;
   static constexpr std::array m_indices{
      0u, 1u, 2u,  // first triangle
      0u, 2u, 3u,  // second triangle
      0u, 3u, 4u,
      0u, 4u, 5u,
      0u, 5u, 6u,
      0u, 6u, 1u,
   };
};

