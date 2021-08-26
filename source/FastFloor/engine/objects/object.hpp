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
      const unsigned int m_id{ 0 };
      static unsigned int counter{ 0 };
  };
}

