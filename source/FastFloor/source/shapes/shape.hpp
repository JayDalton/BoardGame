#pragma once


//#include "base/buffer.hpp"
#include "base/common.hpp"
#include "base/shader.hpp"
#include "base/texture.hpp"
#include "base/transform.hpp"

namespace ogl 
{
   class Ident
   {
      inline static unsigned int counter{ 0 };
      unsigned int m_id{ 0 };

   public:
      Ident() : m_id(counter++) { }
   };


  class Shape : public Ident, public Shader
     //, public Transform // Animation
     //, public Texture
  {
    public:
      //virtual ~Shape() = default;
      
      Shape() = default;
      explicit Shape(
         std::string_view vertex, 
         std::string_view fragment, 
         std::string_view texture);

      virtual void render() const = 0;
      //virtual void update() const = 0;

   private:
      unsigned int m_VBO{ 0 };
      unsigned int m_VAO{ 0 };
      unsigned int m_EBO{ 0 };

      unsigned int m_texture{ 0 };
  };

}
using ShapePtr = std::unique_ptr<ogl::Shape>;

