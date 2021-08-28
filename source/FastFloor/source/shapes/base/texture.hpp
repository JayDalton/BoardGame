#pragma once

//#include <SDL2/SDL_opengl.h>

#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>

namespace ogl 
{
   class Texture
   {
   public:
  	   unsigned id;

   private:
      unsigned compo;
  	   unsigned width;
  	   unsigned height;
  	   unsigned type;
  	   unsigned char* buffer;
      unsigned image_len;

   public:
      Texture(
         unsigned w, 
         unsigned h, 
         float cr = 1, 
         float cg = 1, 
         float cb = 1, 
         float ca = 1
      );

      Texture(
         unsigned w, 
         unsigned h, 
         unsigned type, 
         unsigned char* b
      );

      virtual ~Texture();

      void init();
      void bind();
      void free();

      void draw(
        signed x, 
        signed y, 
        const Texture* tex, 
        float cr = 0, 
        float cg = 0, 
        float cb = 0, 
        float ca = 0
      );

      void fill(
        float cr = 1, 
        float cg = 1, 
        float cb = 1, 
        float ra = 1
      );

      unsigned char* getBuffer() const;
      unsigned getBufferSize() const;
      unsigned getBufferLength() const;
      unsigned getSize() const;
      unsigned getWidth() const;
      unsigned getHeight() const;

      float getAlphaInfo() const;

  	   unsigned getType() const;
  	   unsigned getCompos() const;
  	   std::string getTypeName() const;
      std::string printDetail() const;

      Texture(const Texture& tex);
      Texture& operator=(const Texture& tex);

    private:
       unsigned char cv(float c) const;

  };

}
