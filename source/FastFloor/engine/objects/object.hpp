#pragma once

namespace ogl 
{
   // Ident
   struct Object
   {
      Object()
         : m_id(counter++)
      {
      }

   private:
      unsigned int m_id{ 0 };
      inline static unsigned int counter{ 0 };
  };
}

