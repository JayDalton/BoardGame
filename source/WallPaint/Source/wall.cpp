/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "wall.hpp"

//############################################################################
/** 
*/
//############################################################################  
ogl::Wall::Wall(GLfloat wu, GLfloat wv, GLuint tu, GLuint tv)
  : Rectangle(wu, wv), Texture(tu, tv), fore(0), back(0)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/** 
*/
//############################################################################  
ogl::Wall::Wall(GLfloat wu, GLfloat wv)
  : Rectangle(wu, wv), Texture(wu, wv), fore(0), back(0)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/** 
*/
//############################################################################  
ogl::Wall::~Wall()
{
  Texture::free();
}

//############################################################################
/** 
*/
//############################################################################  
ogl::Wall::Wall(const Wall& original)
  : Rectangle(original), Texture(original)
{
  Texture::init();
  Texture::bind();
  fore = original.fore;
  back = original.back;
}

//############################################################################
/** 
*/
//############################################################################  
ogl::Wall& ogl::Wall::operator=(const Wall& original)
{
  if(this != &original) {
    Rectangle::operator=(original);
    Texture::operator=(original);
    Texture::init();
    Texture::bind();
    fore = original.fore;
    back = original.back;
  }
  return *this;
}

//############################################################################
/** 
*/
//############################################################################  
void ogl::Wall::setForeTexture(const Texture *tex)
{
  fore = tex;
}

//############################################################################
/** 
*/
//############################################################################  
void ogl::Wall::setBackTexture(const Texture *tex)
{
  back = tex;
}

//############################################################################
/**
*/
//############################################################################
void ogl::Wall::fill(GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  Texture::fill(cr, cg, cb, ca);
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
void ogl::Wall::draw(GLint x, GLint y, const Texture* tex, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  Texture::draw(x, y, tex, cr, cg, cb, ca);
  Texture::bind();
}

//############################################################################
/** 
*/
//############################################################################  
bool ogl::Wall::strike(glm::vec3 p1, glm::vec3 p2, Texture *tex)
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
void ogl::Wall::render() const
{
  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glBindTexture(GL_TEXTURE_2D, Texture::id);
  Rectangle::render();  // Mask

  glEnable(GL_BLEND);
  glBlendFunc(GL_DST_ALPHA, GL_ZERO);
  glBindTexture(GL_TEXTURE_2D, fore ? fore->id : 0);
  Rectangle::render();  // Fore

  glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE);
  glBindTexture(GL_TEXTURE_2D, back ? back->id : 0);
  Rectangle::render();  // Back

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
}

