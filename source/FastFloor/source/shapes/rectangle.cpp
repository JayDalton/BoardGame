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

   // // create transformations
   //glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
   //glm::mat4 projection = glm::mat4(1.0f);
   //projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
   //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

   // create transformations
   //glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
   //transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
   //transform = glm::rotate(transform, glm::radians(45.f), glm::vec3(0.0f, 0.0f, 1.0f));

   // render container
   Shader::useShader();
   //Shader::setMat4("transform", transform);
   //Shader::setMat4("view", view);

   glBindVertexArray(m_VAO);
   //glDrawElements(GL_LINE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);
   glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}


Hexagon::~Hexagon()
{
   glDeleteVertexArrays(1, &m_VAO);
   glDeleteBuffers(1, &m_VBO);
   glDeleteBuffers(1, &m_EBO);
}

Hexagon::Hexagon(std::string_view vertex, std::string_view fragment)
   : ogl::Shape(vertex, fragment, ogl::Colors::Red)
{
   //auto circlePoint = [](float angle, float radius) -> glm::vec3
   //{
   //   auto x = radius * std::cos(glm::radians(angle));
   //   auto y = radius * std::sin(glm::radians(angle));
   //   return glm::vec3(x, y, 0);
   //};

   //using Element = std::vector<float>;
   //std::vector<Element> elementList;
   //auto makeElement = [](ogl::Vertex vertex) -> Element
   //{
   //   return { vertex.x, vertex.y, vertex.z,
   //      1.0f, 1.0f, 1.0f, vertex.x, vertex.y };
   //};

   //const float angle{ 60.f };
   //elementList.push_back(makeElement({}));
   //for (int idx = 0; idx < 6; idx++)
   //{
   //   auto point = circlePoint(idx * angle, 1.f);
   //   elementList.push_back(makeElement(point));
   //}

   //for (auto element : elementList)
   //{
   //   m_vertices.insert(m_vertices.end(), element.cbegin(), element.cend());
   //}

   bind();
}


void Hexagon::bind() const
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

void Hexagon::render() const
{
   // bind textures on corresponding texture units
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, Texture::m_id);
   //glActiveTexture(GL_TEXTURE1);
   //glBindTexture(GL_TEXTURE_2D, Texture::m_id2);

   // // create transformations
   //glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
   //glm::mat4 projection = glm::mat4(1.0f);
   //projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
   //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

   // create transformations
   //glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
   //transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
   //transform = glm::rotate(transform, glm::radians(45.f), glm::vec3(0.0f, 0.0f, 1.0f));

   // render container
   Shader::useShader();
   //Shader::setMat4("transform", transform);
   //Shader::setMat4("view", view);

   glBindVertexArray(m_VAO);
   //glDrawElements(GL_LINE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);
   glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}

Rectangle::Rectangle(ogl::Size size, ogl::Color color,
   std::string_view vertex, std::string_view fragment)
   : ogl::Shape(vertex, fragment, color), m_size(size)
{
   // create vertices...


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
