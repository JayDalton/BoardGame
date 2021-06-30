/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "area.hpp"

//############################################################################
/**
*/
//############################################################################
ogl::Area::Area(GLfloat au, GLfloat av, GLuint tu, GLuint tv, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
  : Rectangle(au, av), Texture(tu, tv, cr, cg, cb, ca)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::Area::Area(GLfloat au, GLfloat av, const Texture *tex)
  : Rectangle(au, av), Texture(*tex)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::Area::Area(GLfloat au, GLfloat av, const Texture &tex)
  : Rectangle(au, av), Texture(tex)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::Area::~Area()
{
  Texture::free();
}

//############################################################################
/**
*/
//############################################################################
ogl::Area::Area(const Area& original)
  : Rectangle(original), Texture(original)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::Area& ogl::Area::operator=(const Area& original)
{
  if(this != &original) {
    Rectangle::operator=(original);
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
void ogl::Area::setTexture(const Texture *tex)
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
void ogl::Area::setTexture(const Texture &tex)
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
void ogl::Area::fill(GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  Texture::fill(cr, cg, cb, ca);
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
void ogl::Area::draw(GLint x, GLint y, const ogl::Texture* tex, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  Texture::draw(x, y, tex, cr, cg, cb, ca);
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
bool ogl::Area::strike(glm::vec3 p1, glm::vec3 p2, Texture *tex)
{
  bool result = false;
  glm::vec3 pI (1.0f);
  if (Rectangle::intersect(p1, p2, pI)) {
    GLuint texW (Texture::getWidth());
    GLuint texH (Texture::getHeight());
    Texture::draw(pI.y * texW, pI.z * texH, tex);
    Texture::bind();
    result = true;
  }
  return result;
}

//############################################################################
/**
*/
//############################################################################
void ogl::Area::render() const
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, Texture::id);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  Rectangle::render();

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  glDisable(GL_BLEND);
}
