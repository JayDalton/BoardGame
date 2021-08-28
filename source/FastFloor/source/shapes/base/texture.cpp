#include "texture.hpp"

#include <GL/glew.h>

//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

ogl::Texture::Texture(Size size, Color color)
   : m_width(size.x), m_height(size.y)
   , m_compo(4), m_type(GL_RGBA)
{
   glGenTextures(1, &m_id);
   glBindTexture(GL_TEXTURE_2D, m_id);

   // set the texture wrapping parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   // set texture filtering parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   int length{ m_compo * m_width * m_height };
   std::vector<std::uint8_t> buffer(length, 1);

   glTexImage2D(GL_TEXTURE_2D, 0, m_compo, m_width, m_height, 0, m_type, GL_UNSIGNED_BYTE, buffer.data());
   //glGenerateMipmap(GL_TEXTURE_2D);
}

ogl::Texture::Texture(std::filesystem::path path)
{
   glGenTextures(1, &m_id);
   glBindTexture(GL_TEXTURE_2D, m_id);

   // set the texture wrapping parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   // set texture filtering parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   // load image, create texture and generate mipmaps
   //if (auto* data = stbi_load((const char*)path.c_str(), &m_width, &m_height, &m_compo, 0))
   //{
   //   m_type = (m_compo == 4) ? GL_RGBA : (m_compo == 3) ? GL_RGB : GL_NONE;

   //   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
   //   glGenerateMipmap(GL_TEXTURE_2D);
   //   stbi_image_free(data);
   //}
   //else
   //{
   //   // generate full color
   //   std::cout << "Failed to load texture" << std::endl;
   //   //glTexImage2D(GL_TEXTURE_2D, 0, m_compo, m_width, m_height, 0, m_type, GL_UNSIGNED_BYTE, m_buffer);
   //}
}

ogl::Texture::~Texture()
{
   glDeleteTextures(1, &m_id);
}

std::string ogl::Texture::getTypeName() const
{
  return (m_type == GL_RGBA) 
     ? "GL_RGBA" : (m_type == GL_RGB) 
     ? "GL_RGB" : "GL_???";
}

