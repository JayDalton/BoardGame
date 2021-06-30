/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "ball.hpp"

//############################################################################
/**
*/
//############################################################################
ogl::Ball::Ball(unsigned int recursion, GLuint tu, GLuint tv, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
  : IcoSphere(recursion), Texture(tu, tv, cr, cg, cb, ca)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::Ball::Ball(unsigned int recursion, const Texture *tex)
  : IcoSphere(recursion), Texture(*tex)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::Ball::Ball(unsigned int recursion, const Texture &tex)
  : IcoSphere(recursion), Texture(tex)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::Ball::~Ball()
{
  Texture::free();
}

//############################################################################
/**
*/
//############################################################################
ogl::Ball::Ball(const Ball& original)
  : IcoSphere(original), Texture(original)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::Ball& ogl::Ball::operator=(const Ball& original)
{
  if(this != &original) {
    IcoSphere::operator=(original);
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
void ogl::Ball::setTexture(const Texture *tex)
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
void ogl::Ball::setTexture(const Texture &tex)
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
void ogl::Ball::fill(GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  Texture::fill(cr, cg, cb, ca);
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
void ogl::Ball::draw(GLint x, GLint y, const ogl::Texture* tex, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  Texture::draw(x, y, tex, cr, cg, cb, ca);
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
bool ogl::Ball::strike(glm::vec3 p1, glm::vec3 p2, Texture *tex)
{
  bool result = false;
  //glm::vec3 pI (1.0f);
  //if (Rectangle::intersect(p1, p2, pI)) {
  //  GLuint texW (Texture::getWidth());
  //  GLuint texH (Texture::getHeight());
  //  Texture::draw(pI.y * texW, pI.z * texH, tex);
  //  Texture::bind();
  //  result = true;
  //}
  return result;
}

//############################################################################
/**
*/
//############################################################################
void ogl::Ball::render() const
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, Texture::id);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  IcoSphere::render();

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  glDisable(GL_BLEND);
}
