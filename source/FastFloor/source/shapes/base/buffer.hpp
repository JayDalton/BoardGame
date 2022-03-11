#pragma once

#include "common.hpp"

namespace ogl 
{
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

      static Element create(Vertex vertex, Color color, Coords coords)
      {
         return {
            vertex.x, vertex.y, vertex.z,
            color.r, color.g, color.b,
            coords.x, coords.y
         };
      };

      static Element create(Vertex vertex, Color color)
      {
         auto coords{ (ogl::Coords(vertex) - ogl::Coords(-1.0f, -1.0f)) * 0.5f };

         return {
            vertex.x, vertex.y, vertex.z,
            color.r, color.g, color.b,
            coords.x, coords.y
         };
      };

   protected:
      unsigned int m_VBO{ 0 };
      unsigned int m_VAO{ 0 };
      unsigned int m_EBO{ 0 };
   };

}


