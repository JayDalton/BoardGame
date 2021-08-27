#pragma once

#include <sstream>

namespace ogl 
{
   class Geometry
   {
   public:
      Geometry();
      virtual ~Geometry();
      Geometry(const Geometry& geom);
      Geometry& operator=(const Geometry& geom);

      float* getBuffer(unsigned offset = 0) const;
      unsigned* getIndice(unsigned offset = 0) const;
      unsigned StructSize() const;
      unsigned StructLength() const;
      unsigned BufferSize() const;
      unsigned BufferLength() const;
      unsigned IndiceSize() const;
      unsigned IndiceLength() const;

      std::string getIndiceString() const;
      std::string getBufferString() const;

      void setColor(float r, float g, float b);

   protected:
      float* buffer;
      unsigned* indices;
      unsigned buffer_len;
      unsigned indice_len;
      unsigned struct_len;
   };
}
