#pragma once

#include "common.hpp"

namespace ogl 
{
   struct Texture
   {
      void freeTexture();
      bool createTexture(std::string_view path);

      void useTexture() const;

  	   std::string getTypeName() const;

   private:
      unsigned m_id{ 0 };
      int m_compo{ 0 }; // 3/4
  	   int m_width{ 0 };
  	   int m_height{ 0 };
  	   unsigned m_type{ 0 }; // rgb(a)
  };
}


