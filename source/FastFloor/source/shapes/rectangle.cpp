#include "rectangle.hpp"

#include <GL/glew.h>

Square::Square(std::string_view vertex, 
   std::string_view fragment, std::string_view texture) 
   : ogl::Shape(vertex, fragment, texture)
{
   ogl::Vertex vertex1{ +1.0f, +1.0f, 0.f };
   ogl::Vertex vertex2{ +1.0f, -1.0f, 0.f };
   ogl::Vertex vertex3{ -1.0f, -1.0f, 0.f };
   ogl::Vertex vertex4{ -1.0f, +1.0f, 0.f };

   //addTexture(texture);

   appendElement(makeElement(vertex1));
   appendElement(makeElement(vertex2));
   appendElement(makeElement(vertex3));
   appendElement(makeElement(vertex4));

   bindBuffer({ 0u, 1u, 3u, 1u, 2u, 3u });
}

Square::Square(std::string_view vertex
   , std::string_view fragment, ogl::Color color)
   : ogl::Shape(vertex, fragment, color)
{
   ogl::Vertex vertex1{ +1.0f, +1.0f, 0.f };
   ogl::Vertex vertex2{ +1.0f, -1.0f, 0.f };
   ogl::Vertex vertex3{ -1.0f, -1.0f, 0.f };
   ogl::Vertex vertex4{ -1.0f, +1.0f, 0.f };

   defaultColor(color);
   appendElement(makeElement(vertex1));
   appendElement(makeElement(vertex2));
   appendElement(makeElement(vertex3));
   appendElement(makeElement(vertex4));

   bindBuffer({ 0u, 1u, 3u, 1u, 2u, 3u });
}

Square::~Square()
{
   //glDeleteVertexArrays(1, &m_VAO);
   //glDeleteBuffers(1, &m_VBO);
   //glDeleteBuffers(1, &m_EBO);
}

//void Square::bind() const
//{
//   //glGenVertexArrays(1, &m_VAO);
//   //glGenBuffers(1, &m_VBO);
//   //glGenBuffers(1, &m_EBO);
//
//   //glBindVertexArray(m_VAO);
//
//   //glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//   //glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);
//
//   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
//   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW);
//
//   //// position attribute
//   //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//   //glEnableVertexAttribArray(0);
//   //// color attribute
//   //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//   //glEnableVertexAttribArray(1);
//   //// texture coord attribute
//   //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//   //glEnableVertexAttribArray(2);
//}

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

// #########################################################

Rectangle::~Rectangle()
{
   //glDeleteVertexArrays(1, &m_VAO);
   //glDeleteBuffers(1, &m_VBO);
   //glDeleteBuffers(1, &m_EBO);
}

Rectangle::Rectangle(ogl::SizeF size
   , std::string_view vertex
   , std::string_view fragment
   , ogl::Color color)
   : ogl::Shape(vertex, fragment, color), m_size(size)
{
   auto normal = glm::normalize(size);

   defaultColor(color);
   appendElement(makeElement({ +normal.x, +normal.y, 0.f }));
   appendElement(makeElement({ +normal.x, -normal.y, 0.f }));
   appendElement(makeElement({ -normal.x, -normal.y, 0.f }));
   appendElement(makeElement({ -normal.x, +normal.y, 0.f }));

   bindBuffer({ 0u, 1u, 3u, 1u, 2u, 3u });
}

Rectangle::Rectangle(ogl::SizeF size, std::string_view vertex, 
   std::string_view fragment, std::string_view texture)
   : ogl::Shape(vertex, fragment, texture), m_size()
{
   auto normal = glm::normalize(size);

   // textur coords ???
   appendElement(makeElement({ +normal.x, +normal.y, 0.f }));
   appendElement(makeElement({ +normal.x, -normal.y, 0.f }));
   appendElement(makeElement({ -normal.x, -normal.y, 0.f }));
   appendElement(makeElement({ -normal.x, +normal.y, 0.f }));

   bindBuffer({ 0u, 1u, 3u, 1u, 2u, 3u });
}

ogl::Size Rectangle::getSize() const
{
   return m_size;
}

//void Rectangle::bind() const
//{
//   glGenVertexArrays(1, &m_VAO);
//   glGenBuffers(1, &m_VBO);
//   glGenBuffers(1, &m_EBO);
//
//   glBindVertexArray(m_VAO);
//
//   glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);
//
//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
//   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW);
//
//   // position attribute
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//   glEnableVertexAttribArray(0);
//   // color attribute
//   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//   glEnableVertexAttribArray(1);
//   // texture coord attribute
//   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//   glEnableVertexAttribArray(2);
//}

void Rectangle::render() const
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

// #########################################################

Hexagon::~Hexagon()
{
   //glDeleteVertexArrays(1, &m_VAO);
   //glDeleteBuffers(1, &m_VBO);
   //glDeleteBuffers(1, &m_EBO);
}

Hexagon::Hexagon(std::string_view vertex
   , std::string_view fragment, ogl::Color color)
   : ogl::Shape(vertex, fragment, color)
{
   auto circlePoint = [](float angle, float radius) -> glm::vec3
   {
      auto x = radius * std::cos(glm::radians(angle));
      auto y = radius * std::sin(glm::radians(angle));
      return glm::vec3(x, y, 0);
   };

   ogl::Vertex center{ 0.f };
   appendElement(makeElement(center, color));
   for (auto angle : { 0.f, 60.f, 120.f, 180.f, 240.f, 300.f })
   {
      auto point{ circlePoint(angle, 1.f) };
      appendElement(makeElement(point, color));
   }

   bindBuffer({ 
      0u, 1u, 2u,
      0u, 2u, 3u,
      0u, 3u, 4u,
      0u, 4u, 5u,
      0u, 5u, 6u,
      0u, 6u, 1u,
   });
}

//void Hexagon::bind() const
//{
//   glGenVertexArrays(1, &m_VAO);
//   glGenBuffers(1, &m_VBO);
//   glGenBuffers(1, &m_EBO);
//
//   glBindVertexArray(m_VAO);
//
//   glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);
//
//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
//   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW);
//
//   // position attribute
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//   glEnableVertexAttribArray(0);
//   // color attribute
//   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//   glEnableVertexAttribArray(1);
//   // texture coord attribute
//   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//   glEnableVertexAttribArray(2);
//}

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
