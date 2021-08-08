/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "texmodel.hpp"

//############################################################################
/**
*/
//############################################################################
ogl::TexModel::TexModel(boost::filesystem::path path, GLuint tu, GLuint tv, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
  : ObjModel(path), Texture(tu, tv, cr, cg, cb, ca)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::TexModel::TexModel(boost::filesystem::path path, const Texture *tex)
  : ObjModel(path), Texture(*tex)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::TexModel::TexModel(boost::filesystem::path path, const Texture &tex)
  : ObjModel(path), Texture(tex)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::TexModel::~TexModel()
{
  Texture::free();
}

//############################################################################
/**
*/
//############################################################################
ogl::TexModel::TexModel(const TexModel& original)
  : ObjModel(original), Texture(original)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::TexModel& ogl::TexModel::operator=(const TexModel& original)
{
  if(this != &original) {
    ObjModel::operator=(original);
    Texture::operator=(original);
    Texture::init();
    Texture::bind();
  }
  return *this;
}

//############################################################################
/**
*/
//############################################################################
void ogl::TexModel::setTexture(const Texture *tex)
{
  Texture::free();
  Texture::operator=(*tex);
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
void ogl::TexModel::setTexture(const Texture &tex)
{
  Texture::free();
  Texture::operator=(tex);
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
void ogl::TexModel::fill(GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  Texture::fill(cr, cg, cb, ca);
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
void ogl::TexModel::draw(GLint x, GLint y, const ogl::Texture* tex, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  Texture::draw(x, y, tex, cr, cg, cb, ca);
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
void ogl::TexModel::render() const
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, Texture::id);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  ObjModel::render();

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  glDisable(GL_BLEND);
}
