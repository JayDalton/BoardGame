/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#ifndef OGL_TEXTURE_MANAGER_HPP
#define OGL_TEXTURE_MANAGER_HPP

#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include <boost/filesystem.hpp>
#include <SFML/OpenGL.hpp>

#include "texture.hpp"
#include "tgaloader.hpp"

namespace ogl {

  class TextureManager
  {
    private:
      std::map<const std::string, Texture*>* library;

    public:
      TextureManager();
      ~TextureManager();

      bool loadFilename(boost::filesystem::path p);
      bool loadDirectory(boost::filesystem::path p);
      bool loadDirectoryRecursive(boost::filesystem::path p);

      const Texture* getTexture(std::string name) const;

    private:

  };

}

#endif
