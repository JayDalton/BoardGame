#include "rectangle.hpp"

#include <GL/glew.h>

Square::Square(std::string_view vertex, 
   std::string_view fragment, std::string_view texture) 
   : ogl::Shape(vertex, fragment, texture)
{
   //Shape::bindBuffer();
   bind();
}

Square::Square(std::string_view vertex
   , std::string_view fragment, ogl::Color color)
   : ogl::Shape(vertex, fragment, color)
{
   auto insertElement = [&](std::uint8_t index, Element element)
   {
      std::copy(element.cbegin(), element.cend(),
         m_vertices.at(index).begin());
   };

   auto makeElement = [&color](ogl::Vertex vertex)
   {
      return Element{
         vertex.x, vertex.y, vertex.z,
         color.r, color.g, color.b,
         0.0f, 0.0f };
   };

   auto center = ogl::Vertex{ 0.f };

   ogl::Vertex vertex1{ +1.0f, +1.0f, 0.f };
   ogl::Vertex vertex2{ +1.0f, -1.0f, 0.f };
   ogl::Vertex vertex3{ -1.0f, -1.0f, 0.f };
   ogl::Vertex vertex4{ -1.0f, +1.0f, 0.f };
   insertElement(0, makeElement(vertex1));
   insertElement(1, makeElement(vertex2));
   insertElement(2, makeElement(vertex3));
   insertElement(3, makeElement(vertex4));


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

// #########################################################

Rectangle::~Rectangle()
{
   glDeleteVertexArrays(1, &m_VAO);
   glDeleteBuffers(1, &m_VBO);
   glDeleteBuffers(1, &m_EBO);
}

Rectangle::Rectangle(ogl::SizeF size
   , std::string_view vertex
   , std::string_view fragment
   , ogl::Color color)
   : ogl::Shape(vertex, fragment, color), m_size(size)
{
   auto normal = glm::normalize(size);

   auto insertElement = [&](std::uint8_t index, Element element)
   {
      std::copy(element.cbegin(), element.cend(),
         m_vertices.at(index).begin());
   };

   auto makeElement = [&color](ogl::Vertex vertex)
   {
      return Element{
         vertex.x, vertex.y, vertex.z,
         color.r, color.g, color.b,
         0.0f, 0.0f };
   };

   auto center = ogl::Vertex{ 0.f };

   ogl::Vertex vertex1{ +normal.x, +normal.y, 0.f };
   ogl::Vertex vertex2{ +normal.x, -normal.y, 0.f };
   ogl::Vertex vertex3{ -normal.x, -normal.y, 0.f };
   ogl::Vertex vertex4{ -normal.x, +normal.y, 0.f };
   insertElement(0, makeElement(vertex1));
   insertElement(1, makeElement(vertex2));
   insertElement(2, makeElement(vertex3));
   insertElement(3, makeElement(vertex4));

   bind();
   bindBuffer();
}

Rectangle::Rectangle(ogl::SizeF size, std::string_view vertex, 
   std::string_view fragment, std::string_view texture)
   : ogl::Shape(vertex, fragment, texture), m_size()
{

   bind();
   bindBuffer();
}

ogl::Size Rectangle::getSize() const
{
   return m_size;
}

void Rectangle::bind() const
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
   glDeleteVertexArrays(1, &m_VAO);
   glDeleteBuffers(1, &m_VBO);
   glDeleteBuffers(1, &m_EBO);
}

Hexagon::Hexagon(std::string_view vertex
   , std::string_view fragment, ogl::Color color)
   : ogl::Shape(vertex, fragment, color)
{
   const float angle{ 60.f };
   auto center = ogl::Vertex{ 0.f };

   auto circlePoint = [](float angle, float radius) -> glm::vec3
   {
      auto x = radius * std::cos(glm::radians(angle));
      auto y = radius * std::sin(glm::radians(angle));
      return glm::vec3(x, y, 0);
   };

   auto insertElement = [&](std::uint8_t index, Element element) 
   {
      std::copy(element.cbegin(), element.cend(),
         m_vertices.at(index).begin());
   };

   auto makeElement = [](ogl::Vertex vertex, ogl::Color color)
   {
      return Element{ 
         vertex.x, vertex.y, vertex.z,
         color.r, color.g, color.b, 
         0.0f, 0.0f };
   };

   insertElement(0, makeElement(center, color));
   for (int index = 1; index < 7; index++)
   {
      auto point = circlePoint(index * angle, 1.f);
      insertElement(index, makeElement(point, color));
   }

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
