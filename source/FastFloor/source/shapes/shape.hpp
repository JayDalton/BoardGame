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
      using Element = std::array<VertexType, 8>;

      std::vector<VertexType> m_vertices;
      std::vector<IndexType> m_indices;
      Color m_color{ Colors::White };

      std::int32_t getVerticesSize() const 
      {
         return sizeof(VertexType) * m_vertices.size();
      }

      std::int32_t getIndicesSize() const
      {
         return sizeof(IndexType) * m_indices.size();
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
     , public Texture
  {
    public:
      virtual ~Shape();

      virtual void render(Matrix pos) const = 0;
      //virtual void update() const = 0;
      //virtual void start() const = 0;
      //virtual void stop() const = 0;

   protected:
      void bindBuffer(std::vector<unsigned>&& indices);

   protected:
      unsigned int m_id{ 0 };
      unsigned int m_VBO{ 0 };
      unsigned int m_VAO{ 0 };
      unsigned int m_EBO{ 0 };
  };

  struct Drawable
  {
      unsigned m_shapeId{ 0 }; // geometry
      Vertex m_position{ 0 };  // raus
      // calculated matrix

      // Texture
      // Shader
      using ShaderType = std::variant<glm::mat4, glm::vec3>;
      std::unordered_map<std::string, ShaderType> m_shader;

      void update(Duration delta)
      {
         // ???
      }

      Matrix getPosition() const
      {
         return glm::translate(Matrix{ 1.0f }, m_position);
      }
  };

}
using ShapePtr = std::unique_ptr<ogl::Shape>;

