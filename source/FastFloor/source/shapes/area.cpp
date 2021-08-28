#include "area.hpp"

#include <GL/glew.h>

ogl::Area::Area(GLfloat au, GLfloat av, GLuint tu, GLuint tv, Color color)
   : Rectangle(au, av), Texture({ tu, tv }, color)
{
}

void ogl::Area::fill(Color color)
{
  //Texture::fill(cr, cg, cb, ca);
}

void ogl::Area::draw(GLint x, GLint y, const ogl::Texture* tex, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  //Texture::draw(x, y, tex, cr, cg, cb, ca);
}

bool ogl::Area::strike(glm::vec3 p1, glm::vec3 p2, Texture *tex)
{
  bool result = false;
  //glm::vec3 pI (1.0f);
  //if (Rectangle::intersect(p1, p2, pI)) {
  //  GLuint texW (Texture::getWidth());
  //  GLuint texH (Texture::getHeight());
  //  Texture::draw(pI.y * texW, pI.z * texH, tex);
  //  //Texture::bind();
  //  result = true;
  //}
  return result;
}

void ogl::Area::render() const
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, Texture::m_id);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  Rectangle::render();

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  glDisable(GL_BLEND);
}
