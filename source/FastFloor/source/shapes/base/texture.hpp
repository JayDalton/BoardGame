#pragma once

#include "common.hpp"

namespace ogl 
{
   struct Texture
   {
      unsigned int m_id{ 0 };

      ~Texture();

   protected:
      bool createTexture(std::string_view path);

  	   std::string getTypeName() const;

   private:
      int m_compo{ 0 }; // 3/4
  	   int m_width{ 0 };
  	   int m_height{ 0 };
  	   unsigned m_type{ 0 }; // rgb(a)
  };
}


