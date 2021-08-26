#pragma once

#include <SDL2/SDL_opengl.h>

namespace ogl {

   struct Object
   {
      Object()
         : m_id(counter++)
      {
      }

   private:
      const unsigned int m_id{ 0 };
      static unsigned int counter{ 0 };
  };
}

