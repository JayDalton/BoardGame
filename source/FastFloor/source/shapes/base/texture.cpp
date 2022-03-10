#include "texture.hpp"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

ogl::Texture::~Texture()
{
   glDeleteTextures(1, &m_id);
}

bool ogl::Texture::createTexture(std::string_view path)
{
   glGenTextures(1, &m_id);
   glBindTexture(GL_TEXTURE_2D, m_id);

   // set the texture wrapping parameters
   // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   // set texture filtering parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   // load image, create texture and generate mipmaps
   stbi_set_flip_vertically_on_load(true);//cause images the way OpenGL expects
   if (auto* data = stbi_load(path.data(), &m_width, &m_height, &m_compo, 0))
   {
      m_type = (m_compo == 4) ? GL_RGBA : (m_compo == 3) ? GL_RGB : GL_NONE;

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, m_type, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      stbi_image_free(data);
      return true;
   }

   std::cout << "Failed to load texture" << std::endl;
   return false;
}

void ogl::Texture::useTexture()
{
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, m_id);
}

std::string ogl::Texture::getTypeName() const
{
  return (m_type == GL_RGBA) 
     ? "GL_RGBA" : (m_type == GL_RGB) 
     ? "GL_RGB" : "GL_???";
}

