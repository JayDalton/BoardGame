#include "rectangle.hpp"

#include <GL/glew.h>

Square::Square(std::string_view vertex, 
   std::string_view fragment, std::string_view texture) 
   : ogl::Shape(vertex, fragment, texture)
{
   //Shape::bindBuffer();
   bind();
}

Square::Square(std::string_view vertex, std::string_view fragment)
   : ogl::Shape(vertex, fragment)
{
   bind();
}

Square::~Square()
{
   glDeleteVertexArrays(1, &m_VAO);
   glDeleteBuffers(1, &m_VBO);
   glDeleteBuffers(1, &m_EBO);
}

void Square::bind() const
{
   glGenVertexArrays(1, &m_VAO);
   glGenBuffers(1, &m_VBO);
   glGenBuffers(1, &m_EBO);

   glBindVertexArray(m_VAO);

   glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   // color attribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);
   // texture coord attribute
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
   glEnableVertexAttribArray(2);
}

void Square::render() const
{
   // bind textures on corresponding texture units
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, Texture::m_id);
   //glActiveTexture(GL_TEXTURE1);
   //glBindTexture(GL_TEXTURE_2D, Texture::m_id2);

   // render container
   Shader::useShader();
   glBindVertexArray(m_VAO);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Rectangle::Rectangle(ogl::Size size, ogl::Color color,
   std::string_view vertex, std::string_view fragment)
   : ogl::Shape(vertex, fragment, color), m_size(size)
{
   bindBuffer();
}

Rectangle::Rectangle(ogl::Size size, std::string_view vertex, 
   std::string_view fragment, std::string_view texture)
   : ogl::Shape(vertex, fragment, texture), m_size()
{
   bindBuffer();
}

ogl::Size Rectangle::getSize() const
{
   return m_size;
}

void Rectangle::render() const
{
  //glEnableClientState(GL_VERTEX_ARRAY);
  //glEnableClientState(GL_NORMAL_ARRAY);
  //glEnableClientState(GL_COLOR_ARRAY);

  //glVertexPointer(3, GL_FLOAT, StructSize(), getBuffer());
  //glNormalPointer(GL_FLOAT, StructSize(), getBuffer(3));
  //glColorPointer(3, GL_FLOAT, StructSize(), getBuffer(6));
  //glTexCoordPointer(2, GL_FLOAT, StructSize(), getBuffer(9));
  //glDrawElements(GL_TRIANGLES, IndiceLength(), GL_UNSIGNED_INT, getIndice());

  //glDisableClientState(GL_COLOR_ARRAY);
  //glDisableClientState(GL_NORMAL_ARRAY);
  //glDisableClientState(GL_VERTEX_ARRAY);
}
