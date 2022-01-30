#pragma once

#include "base/common.hpp"
#include "base/shader.hpp"
#include "base/texture.hpp"
#include "base/transform.hpp"

namespace ogl 
{
   using Element = std::array<float, 8>;

   enum class Class { Shape, Object };

   struct Ident
   {
      std::int16_t m_ident{ -1 };
      auto operator<=>(const Ident&) const = default;
      explicit operator bool() const { return m_ident != -1; }
   };

   struct Geometry
   {
      static Vertex circlePoint(float angle, float radius)
      {
         auto x = radius * std::cos(glm::radians(angle));
         auto y = radius * std::sin(glm::radians(angle));
         return Vertex(x, y, 0);
      };
      static Vertex circlePoint(Vertex center, float angle, float radius)
      {
         auto x = center.x + radius * std::cos(glm::radians(angle));
         auto y = center.y + radius * std::sin(glm::radians(angle));
         return Vertex(x, y, center.z);
      };
      static Coords texPoint(Vertex vertex, Coords base)
      {
         return (ogl::Coords(vertex) + base) * 0.5f;
      };
   };

   struct Buffer
   {
      std::vector<float> m_vertices;
      std::vector<unsigned> m_indices;
      Color m_color{ Colors::White };

      std::int32_t getVerticesSize() const 
      {
         return sizeof(float) * m_vertices.size();
      }

      std::int32_t getIndicesSize() const
      {
         return sizeof(unsigned) * m_indices.size();
      }

      void append(Element element)
      {
         std::copy(element.cbegin(), element.cend(),
            std::back_inserter(m_vertices));
      };

      Element create(Vertex vertex, Coords coords)
      {
         return {
            vertex.x, vertex.y, vertex.z,
            m_color.r, m_color.g, m_color.b,
            coords.x, coords.y 
         };
      };
      Element create(Coords uvBase, Vertex vertex)
      {
         auto coords{ (ogl::Coords(vertex) - uvBase) * 0.5f };

         return {
            vertex.x, vertex.y, vertex.z,
            m_color.r, m_color.g, m_color.b,
            coords.x, coords.y 
         };
      };
      Element create(Vertex vertex, Color color)
      {
         return {
            vertex.x, vertex.y, vertex.z,
            color.r, color.g, color.b,
            0.0f, 0.0f 
         };
      };
   };

  class Shape : 
     public Ident
     , public Buffer
     , public Shader
     , public Geometry
     //, public Transform // Animation
     , public Texture
  {
    public:
      virtual ~Shape();

      virtual void render() const = 0;
      //virtual void update() const = 0;
      //virtual void start() const = 0;
      //virtual void stop() const = 0;

   protected:
      void bindBuffer(const std::vector<unsigned>& indices);

   protected:
      unsigned int m_id{ 0 };
      unsigned int m_VBO{ 0 };
      unsigned int m_VAO{ 0 };
      unsigned int m_EBO{ 0 };
  };

  struct Moveable
  {
     int m_shapeId{ 0 };
     Vertex m_position;
     // matrix
  };

}
using ShapePtr = std::unique_ptr<ogl::Shape>;

