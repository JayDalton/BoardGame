/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_TGA_LOADER_HPP
#define OGL_TGA_LOADER_HPP

#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#include <boost/filesystem.hpp>

#include <SFML/OpenGL.hpp>

#include "texture.hpp"

namespace ogl {

  class TGALoader
  {
    public:
      const static char uTGAcompare[12];
      const static char cTGAcompare[12];

    private:
      int memsize;
      char* memblock;

    public:
      TGALoader();
      bool load(boost::filesystem::path p, ogl::Texture*& tex);

    private:
      GLubyte cv(GLfloat c) const;
      bool loadUncompressedTGA(ogl::Texture*& tex);
      bool loadCompressedTGA(ogl::Texture*& tex);

  };
}

#endif