#pragma once

#include "base/common.hpp"
#include "base/shader.hpp"
#include "base/texture.hpp"
#include "base/transform.hpp"

namespace ogl 
{
   struct Ident
   {
      std::int16_t m_ident{ -1 };
      auto operator<=>(const Ident&) const = default;
      explicit operator bool() const { return m_ident != -1; }
      std::size_t operator()(const Ident& k) const
      {
         return std::hash<int>()(m_ident);
      }
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
      using VertexType = float;
      using IndexType = unsigned;

      // Element: x, y, z, r, g, b, u, v
      using Element = std::array<VertexType, 8>;

      std::vector<VertexType> m_vertices;
      std::vector<IndexType> m_indices;
      Color m_color{ Colors::White };
      unsigned m_indexSize{};
      unsigned m_vertexSize{};

      //~Buffer();

      void freeBuffer();
      void bindBuffer(
         const std::vector<Element>& vertices,
         const std::vector<IndexType>& indices
      );

      static auto zipElementList(std::vector<Element>&& elementList)
      {
         std::vector<VertexType> vertexBuffer;
         vertexBuffer.reserve(elementList.size() * sizeof(VertexType));
         for (auto&& element : elementList)
         {
            std::copy(element.cbegin(), element.cend(), std::back_inserter(vertexBuffer));
         }
         return vertexBuffer;
      }

      void render();

      std::int32_t getVerticesByteSize() const 
      {
         return sizeof(VertexType) * m_vertexSize;
      }

      std::int32_t getIndicesByteSize() const
      {
         return sizeof(IndexType) * m_indexSize;
      }

      void append(Element element)
      {
         std::copy(element.cbegin(), element.cend(),
            std::back_inserter(m_vertices));
      };

      //void create(std::vector<Element> geometry)
      //{
      //   std::copy(element.cbegin(), element.cend(),
      //      std::back_inserter(m_vertices));
      //};

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

      static Element create(Vertex vertex, Color color, Coords uvBase)
      {
         auto coords{ (ogl::Coords(vertex) - uvBase) * 0.5f };

         return {
            vertex.x, vertex.y, vertex.z,
            color.r, color.g, color.b,
            coords.x, coords.y 
         };
      };

      static Element create(Vertex vertex, Color color)
      {
         return {
            vertex.x, vertex.y, vertex.z,
            color.r, color.g, color.b,
            0.0f, 0.0f 
         };
      };

   protected:
      unsigned int m_VBO{ 0 };
      unsigned int m_VAO{ 0 };
      unsigned int m_EBO{ 0 };
   };

  class Shape : 
     public Ident
     , public Buffer
     , public Shader
     , public Texture
     , public Geometry
  {
    public:
      virtual ~Shape();

      virtual void render(Matrix pos) const = 0;
      //static void render(Buffer& buffer, Shader& shader);

   protected:
      void bindBuffer(std::vector<unsigned>&& indices);
      //void bindBuffer(
      //   const std::vector<Element>& vertices,
      //   const std::vector<IndexType>& indices
      //);

   protected:
      unsigned int m_VBO{ 0 };
      unsigned int m_VAO{ 0 };
      unsigned int m_EBO{ 0 };
  };

}
using ShapePtr = std::unique_ptr<ogl::Shape>;

