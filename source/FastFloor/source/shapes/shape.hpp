#pragma once


//#include "base/buffer.hpp"
#include "base/common.hpp"
#include "base/shader.hpp"
#include "base/texture.hpp"
#include "base/transform.hpp"

namespace ogl 
{
   using Element = std::array<float, 8>;

   template <std::size_t SIZE>
   using ObjectList = std::array<Element, SIZE>;

   struct Ident
   {
      //unsigned int m_id{ 0 };
      //unsigned int m_VBO{ 0 };
      //unsigned int m_VAO{ 0 };
      //unsigned int m_EBO{ 0 };

      //Ident() //: m_id(counter++) 
      //{
      //   static unsigned int counter{ 0 };
      //   m_id = counter++;
      //}
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

      void defaultColor(Color color)
      {
         m_color = color;
      }

      void appendElement(Element element)
      {
         std::copy(element.cbegin(), element.cend(),
            std::back_inserter(m_vertices));
      };

      Element makeElement(ogl::Vertex vertex)
      {
         return {
            vertex.x, vertex.y, vertex.z,
            m_color.r, m_color.g, m_color.b,
            0.0f, 0.0f 
         };
      };

      Element makeElement(ogl::Vertex vertex, ogl::Color color)
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
     //, public Transform // Animation
     , public Texture
  {
    public:
      virtual ~Shape();
      //Shape() = default;

      explicit Shape(
         std::string_view vertex,
         std::string_view fragment,
         std::string_view texture)
         : Shader(vertex, fragment)
         , Texture(texture) {}

      explicit Shape(
         std::string_view vertex,
         std::string_view fragment,
         Color color = { 1.f, 1.f, 1.f, 1.f })
         : Shader(vertex, fragment)
         , Texture({ 1, 1 }, color) {}

      //virtual void bind() const = 0;
      virtual void render() const = 0;
      //virtual void update() const = 0;
      //virtual void stop() const = 0;

   protected:
      void bindBuffer(const std::vector<unsigned>& indices);

   protected:
      unsigned int m_id{ 0 };
      unsigned int m_VBO{ 0 };
      unsigned int m_VAO{ 0 };
      unsigned int m_EBO{ 0 };
  };
}
using ShapePtr = std::unique_ptr<ogl::Shape>;

