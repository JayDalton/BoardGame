/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "cube.hpp"

//############################################################################
/**
*/
//############################################################################
ogl::Cube::Cube(GLfloat cu, GLfloat cv, GLfloat cw, GLuint tu, GLuint tv)
  : Cuboid(cu, cv, cw), Texture(tu, tv), fore(0), back(0)
{
  Texture::init();
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
ogl::Cube::~Cube()
{
  Texture::free();
}

//############################################################################
/**
*/
//############################################################################
ogl::Cube::Cube(const Cube& original)
  : Cuboid(original), Texture(original)
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
ogl::Cube& ogl::Cube::operator=(const Cube& original)
{
  if(this != &original) {
    Cuboid::operator=(original);
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
void ogl::Cube::setForeTexture(const Texture *tex)
{
  fore = tex;
}

//############################################################################
/**
*/
//############################################################################
void ogl::Cube::setBackTexture(const Texture *tex)
{
  back = tex;
}

//############################################################################
/**
*/
//############################################################################
void ogl::Cube::fill(GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  Texture::fill(cr, cg, cb, ca);
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
void ogl::Cube::draw(GLint x, GLint y, const Texture* tex, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  Texture::draw(x, y, tex, cr, cg, cb, ca);
  Texture::bind();
}

//############################################################################
/**
*/
//############################################################################
bool ogl::Cube::strike(glm::vec3 p1, glm::vec3 p2, Texture *tex)
{
  bool result = false;
  GLuint plane = 0;
  glm::vec3 pI (1.0f);
  if (Cuboid::intersect(p1, p2, pI, plane)) {
    std::vector<GLfloat> uv (Cuboid::planeUVs()[plane]);
    GLuint texW (Texture::getWidth());
    GLuint texH (Texture::getHeight());
    Texture::draw(
      uv[0] * texW + pI.y * texW / 3,
      uv[1] * texH + pI.z * texH / 2,
      tex
    );
    Texture::bind();
    result = true;
  }
  return result;
}

//############################################################################
/**
*/
//############################################################################
void ogl::Cube::render() const
{
  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glBindTexture(GL_TEXTURE_2D, Texture::id);
  Cuboid::render();  // Mask

  glEnable(GL_BLEND);
  glBlendFunc(GL_DST_ALPHA, GL_ZERO);
  glBindTexture(GL_TEXTURE_2D, fore ? fore->id : 0);
  Cuboid::render();  // Fore

  glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE);
  glBindTexture(GL_TEXTURE_2D, back ? back->id : 0);
  Cuboid::render();  // Back

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
}
