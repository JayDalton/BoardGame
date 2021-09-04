#pragma once


//#include "base/buffer.hpp"
#include "base/common.hpp"
#include "base/shader.hpp"
#include "base/texture.hpp"
#include "base/transform.hpp"

namespace ogl 
{
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

  class Shape : 
     public Ident
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

      virtual void bind() const = 0;
      virtual void render() const = 0;
      //virtual void update() const = 0;
      //virtual void stop() const = 0;

      static glm::vec2 circlePoint(glm::vec2 center, float angle, float radius);

   protected:
      using Element = std::array<float, 8>;

      void bindBuffer();

   protected:
      unsigned int m_id{ 0 };
      //unsigned int m_VBO{ 0 };
      //unsigned int m_VAO{ 0 };
      //unsigned int m_EBO{ 0 };

      //std::vector<float> m_vertices;
      //std::vector<std::uint32_t> m_indices;
  };
}
using ShapePtr = std::unique_ptr<ogl::Shape>;

