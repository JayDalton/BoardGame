/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "texturemanager.hpp"

//############################################################################
/**
*/
//############################################################################
ogl::TextureManager::TextureManager()
{
  library = new std::map<const std::string, Texture*>();
}

//############################################################################
/**
*/
//############################################################################
ogl::TextureManager::~TextureManager()
{
}

//############################################################################
/**
*/
//############################################################################
bool ogl::TextureManager::loadFilename(boost::filesystem::path p)
{
  bool result = false;

  ogl::Texture* tex (0);
  ogl::TGALoader* loader (new ogl::TGALoader());

  namespace fs = boost::filesystem;

  try
  {
    if (fs::exists(p)) {

      if (0 == (p.extension().compare(std::string(".tga")))) {

        if (loader->load(p, tex)) {

          tex->init();
          tex->bind();

          library->insert(
            std::pair<const std::string, Texture*>(p.filename().generic_string(), tex)
          );

        }
      }

      result = true;

    } else {
      std::cout << p << " does not exist" << std::endl;
    }

  } catch (const fs::filesystem_error& ex) {
    std::cout << ex.what() << std::endl;
  }

  return result;
}

//############################################################################
/**
*/
//############################################################################
bool ogl::TextureManager::loadDirectory(boost::filesystem::path p)
{
  bool result = false;

  ogl::Texture* tex (0);
  ogl::TGALoader* loader (new ogl::TGALoader());

  namespace fs = boost::filesystem;

  try
  {
    if (fs::exists(p) && fs::is_directory(p)) {

      for ( fs::directory_iterator end, dir(p); dir != end; ++dir ) {

        if (0 == (*dir).path().extension().compare(std::string(".tga"))) {

          if (loader->load((*dir).path(), tex)) {

            tex->init();
            tex->bind();

            library->insert(
              std::pair<const std::string, Texture*>((*dir).path().filename().generic_string(), tex)
            );

          }
        }
      }

      result = true;

    } else {
      std::cout << p << " does not exist" << std::endl;
    }

  } catch (const fs::filesystem_error& ex) {
    std::cout << ex.what() << std::endl;
  }

  return result;
}

//############################################################################
/**
*/
//############################################################################
bool ogl::TextureManager::loadDirectoryRecursive(boost::filesystem::path p)
{
  bool result = false;

  ogl::Texture* tex (0);
  ogl::TGALoader* loader (new ogl::TGALoader());

  namespace fs = boost::filesystem;

  try
  {
    if (fs::exists(p) && fs::is_directory(p)) {

      for ( fs::recursive_directory_iterator end, dir(p); dir != end; ++dir ) {

        if (0 == (*dir).path().extension().compare(std::string(".tga"))) {

          if (loader->load((*dir).path(), tex)) {

            tex->init();
            tex->bind();

            library->insert(
              std::pair<std::string, Texture*>((*dir).path().generic_string(), tex)
            );

          }
        }
      }

      result = true;

    } else {
      std::cout << p << " does not exist" << std::endl;
    }

  } catch (const fs::filesystem_error& ex) {
    std::cout << ex.what() << std::endl;
  }

  return result;
}

//############################################################################
/**
*/
//############################################################################
const ogl::Texture* ogl::TextureManager::getTexture(std::string name) const
{
  Texture* result = 0;
  try {
    result = library->at(name);
  } catch (const std::out_of_range& oor) {
    std::cerr << "Out of Range error: " << oor.what() << '\n';
  }
  return result;
}
