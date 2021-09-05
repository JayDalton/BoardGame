#pragma once

#include "common.hpp"

namespace ogl 
{
   struct Texture
   {
      unsigned int m_id{ 0 };

      ~Texture();
      //Texture() = default;

      //explicit Texture(std::filesystem::path path);
      //explicit Texture(Size size, Color color);

   protected:
      bool createTexture(std::string_view path);

      friend std::ostream& operator<<(std::ostream& os, const Texture& tex);

  	   std::string getTypeName() const;

   private:
      int m_compo{ 0 }; // 3/4
  	   int m_width{ 0 };
  	   int m_height{ 0 };
  	   unsigned m_type{ 0 }; // rgb(a)
  };

   //std::ostream& operator<<(std::ostream& os, const Texture& tex)
   //{
   //   // write obj to stream
   //   os << "ID: " << tex.m_id;
   //   os << " W: " << tex.m_width;
   //   os << " H: " << tex.m_height;

   //   return os;
   //}
}


