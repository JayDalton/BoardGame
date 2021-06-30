/*###############################################################################
  Kodierung: UTF-8 ohne BOM - äüö
###############################################################################*/

#include "texture.hpp"

//############################################################################
/**
*/
//############################################################################
ogl::Texture::Texture(GLuint w, GLuint h, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
  : id(0), compo(4), width(w), height(h), type(GL_RGBA), buffer(0)
{
  image_len = compo * width * height;
  buffer = new GLubyte[image_len];
  fill(cr, cg, cb, ca);
}

//############################################################################
/**
*/
//############################################################################
ogl::Texture::Texture(GLuint w, GLuint h, GLuint t, GLubyte* b)
  : id(0), compo(0), width(w), height(h), type(t), buffer(b)
{
  compo = (type == GL_RGBA) ? 4 : 3;
  image_len = compo * width * height;
}

//############################################################################
/**
*/
//############################################################################
ogl::Texture::~Texture()
{
  glDeleteTextures(1, &id);
  if (buffer) {
    delete buffer;
    buffer = 0;
  }
}

//############################################################################
/**
*/
//############################################################################
ogl::Texture::Texture(const ogl::Texture& original)
{
  id = original.id;
  width = original.width;
  height = original.height;
  type = original.type;
  compo = original.compo;
  image_len = original.image_len;

  buffer = new GLubyte[image_len];
  for (unsigned int i = 0; i < image_len; i++) {
    buffer[i] = original.buffer[i];
  }
}

//############################################################################
/**
*/
//############################################################################
ogl::Texture& ogl::Texture::operator=(const ogl::Texture& original)
{
  if (this != &original) {
    width = original.width;
    height = original.height;
    type = original.type;
    compo = original.compo;
    image_len = original.image_len;

    if (buffer) {delete buffer;}
    buffer = new GLubyte[image_len];
    for (unsigned int i = 0; i < image_len; i++) {
      buffer[i] = original.buffer[i];
    }
  }
  return *this;
}

//############################################################################
/**
*/
//############################################################################
void ogl::Texture::init()
{
  glGenTextures(1, &id);
}

//############################################################################
/**
*/
//############################################################################
void ogl::Texture::free()
{
  glDeleteTextures(1, &id);
}

//############################################################################
/**
*/
//############################################################################
void ogl::Texture::bind()
{
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, compo, width, height, 0, type, GL_UNSIGNED_BYTE, buffer);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

//############################################################################
/**
*/
//############################################################################
GLuint ogl::Texture::getSize() const
{
  return width * height;
}

//############################################################################
/**
*/
//############################################################################
GLuint ogl::Texture::getWidth() const
{
  return width;
}

//############################################################################
/**
*/
//############################################################################
GLuint ogl::Texture::getHeight() const
{
  return height;
}

//############################################################################
/**
*/
//############################################################################
GLuint ogl::Texture::getType() const
{
  return type;
}

//############################################################################
/**
*/
//############################################################################
std::string ogl::Texture::getTypeName() const
{
  return (type == GL_RGBA) ? "GL_RGBA" : (type == GL_RGB) ? "GL_RGB" : "GL_?";
}

//############################################################################
/**
*/
//############################################################################
GLuint ogl::Texture::getCompos() const
{
  return compo;
}

//############################################################################
/**
*/
//############################################################################
GLubyte* ogl::Texture::getBuffer() const
{
  return buffer;
}

//############################################################################
/**
*/
//############################################################################
GLuint ogl::Texture::getBufferLength() const
{
  return image_len;
}

//############################################################################
/**
*/
//############################################################################
GLuint ogl::Texture::getBufferSize() const
{
  return image_len * sizeof(GLubyte);
}

//############################################################################
/**
*/
//############################################################################
void ogl::Texture::fill(GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  GLubyte r = cv(cr);
  GLubyte g = cv(cg);
  GLubyte b = cv(cb);
  GLubyte a = cv(ca);
  for (GLubyte* p = buffer; p < buffer + image_len; p += compo) {
    *(p + 0) = r;
    *(p + 1) = g;
    *(p + 2) = b;
    *(p + 3) = a;
  }
}

//############################################################################
/**
*/
//############################################################################
void ogl::Texture::draw(GLint x, GLint y, const ogl::Texture* tex, GLfloat cr, GLfloat cg, GLfloat cb, GLfloat ca)
{
  if (0 != tex && 0 != tex->getBuffer()) {

    GLubyte r = cv(cr);
    GLubyte g = cv(cg);
    GLubyte b = cv(cb);
    GLubyte a = cv(ca);

    GLuint holeW = tex->getWidth();
    GLuint holeH = tex->getHeight();
  	GLuint holeC = tex->getCompos();
    GLubyte *holeB = tex->getBuffer();

    GLfloat holeWhalf = holeW * 0.5f;
    GLfloat holeHhalf = holeH * 0.5f;

    if (
      -holeWhalf < x && x < width + holeWhalf &&
      -holeHhalf < y && y < height + holeHhalf
      ) {

      GLuint offsetX = x < holeWhalf ? holeWhalf - x : 0;
      GLuint startX = 0 < offsetX ? 0 : x - holeWhalf;
      GLuint endeX = (x + holeWhalf) < width ? x + holeWhalf : width;

      GLuint offsetY = y - holeHhalf < 0 ? holeHhalf - y : 0;
      GLuint startY = offsetY ? 0 : y - holeHhalf;
      GLuint endeY = (y + holeHhalf) < height ? y + holeHhalf : height;

      for (
        unsigned int rowMask = startY, rowHole = offsetY;
        rowMask < endeY && rowHole < holeH;
        rowMask++, rowHole++
        ) {

        GLubyte* colMask = buffer + (rowMask * width * compo);
        GLubyte* colHole = holeB + (rowHole * holeW * holeC) + (offsetX * holeC);

        for (
          GLubyte* m = colMask + (startX * compo), *h = colHole;
          m < colMask + (endeX * compo) && h < colHole + (holeW * holeC);
          m += compo, h += holeC
          ) {

          if (((*(h + 0) + *(h + 1) + *(h + 2)) / 3) < 0x20) {
            *(m + 0) = r;
            *(m + 1) = g;
            *(m + 2) = b;
            *(m + 3) = a;
          }
        }
      }
    }
  }
}

//############################################################################
/**
*/
//############################################################################
GLfloat ogl::Texture::getAlphaInfo() const
{
  GLfloat count = 0;
  std::stringstream ss;
  if (0 != buffer && 0 < image_len) {
    for (GLubyte* p = buffer + compo - 1; p < buffer + image_len; p+=compo) {
      if (*p == 0x00) {
        count++;
      }
    }
  }
  return (count / (width * height));
}

//############################################################################
/**
*/
//############################################################################
GLubyte ogl::Texture::cv(GLfloat v) const
{
  return static_cast<GLubyte>(v * 255);
}

//############################################################################
/**
*/
//############################################################################
std::string ogl::Texture::printDetail() const
{
  std::stringstream ss;
  ss << std::endl;
  ss << "ID: " << id;
	ss << " W: " << width;
	ss << " H: " << height;
  ss << " L: " << image_len;
  ss << " B: " << &buffer;
  return ss.str();
}
