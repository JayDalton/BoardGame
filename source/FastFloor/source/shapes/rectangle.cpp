#include "rectangle.hpp"

#include <GL/glew.h>

Square::Square(std::string_view vertex, 
   std::string_view fragment, std::string_view texture) 
{
   append(create({ +1.0f, +1.0f, 0.f }, { 1.0f, 1.0f }));
   append(create({ +1.0f, -1.0f, 0.f }, { 1.0f, 0.0f }));
   append(create({ -1.0f, -1.0f, 0.f }, { 0.0f, 0.0f }));
   append(create({ -1.0f, +1.0f, 0.f }, { 0.0f, 1.0f }));

   bindBuffer({ 0u, 1u, 3u, 1u, 2u, 3u });
   createShaders(vertex, fragment);
   createTexture(texture);
}

Square::Square(std::string_view vertex
   , std::string_view fragment, ogl::Color color)
{
   append(create({ +1.0f, +1.0f, 0.f }, color));
   append(create({ +1.0f, -1.0f, 0.f }, color));
   append(create({ -1.0f, -1.0f, 0.f }, color));
   append(create({ -1.0f, +1.0f, 0.f }, color));

   bindBuffer({ 0u, 1u, 3u, 1u, 2u, 3u });
   createShaders(vertex, fragment);
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

Rectangle::Rectangle(ogl::SizeF size
   , std::string_view vertex
   , std::string_view fragment
   , ogl::Color color)
{
   auto normal = glm::normalize(size);

   append(create({ +normal.x, +normal.y, 0.f }, color));
   append(create({ +normal.x, -normal.y, 0.f }, color));
   append(create({ -normal.x, -normal.y, 0.f }, color));
   append(create({ -normal.x, +normal.y, 0.f }, color));

   bindBuffer({ 0u, 1u, 3u, 1u, 2u, 3u });
   createShaders(vertex, fragment);
}

Rectangle::Rectangle(ogl::SizeF size
   , std::string_view vertex
   , std::string_view fragment
   , std::string_view texture)
{
   auto normal = glm::normalize(size);

   append(create({ +normal.x, +normal.y, 0.f }, { 1.0f, 1.0f }));
   append(create({ +normal.x, -normal.y, 0.f }, { 1.0f, 0.0f }));
   append(create({ -normal.x, -normal.y, 0.f }, { 0.0f, 0.0f }));
   append(create({ -normal.x, +normal.y, 0.f }, { 0.0f, 1.0f }));

   bindBuffer({ 0u, 1u, 3u, 1u, 2u, 3u });
   createShaders(vertex, fragment);
   createTexture(texture);
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

Hexagon::Hexagon(std::string_view vertex
   , std::string_view fragment, ogl::Color color)
{
   auto circlePoint = [](float angle, float radius) -> glm::vec3
   {
      auto x = radius * std::cos(glm::radians(angle));
      auto y = radius * std::sin(glm::radians(angle));
      return glm::vec3(x, y, 0);
   };

   ogl::Vertex center{ 0.f };
   append(create(center, color));
   for (auto angle : { 0.f, 60.f, 120.f, 180.f, 240.f, 300.f })
   {
      auto point{ circlePoint(angle, 1.f) };
      append(create(point, color));
   }

   bindBuffer({ 
      0u, 1u, 2u,
      0u, 2u, 3u,
      0u, 3u, 4u,
      0u, 4u, 5u,
      0u, 5u, 6u,
      0u, 6u, 1u,
   });
   createShaders(vertex, fragment);
}

Hexagon::Hexagon(std::string_view vertex
   , std::string_view fragment
   , std::string_view texture)
{
   auto circlePoint = [](float angle, float radius) -> glm::vec3
   {
      auto x = radius * std::cos(glm::radians(angle));
      auto y = radius * std::sin(glm::radians(angle));
      return glm::vec3(x, y, 0);
   };

   append(create(ogl::Vertex{ 0.f }, { 0.0f, 0.0f }));
   append(create(circlePoint(000.f, 1.f), { 0.0f, 0.0f }));
   append(create(circlePoint(060.f, 1.f), { 1.0f, 1.0f }));
   append(create(circlePoint(120.f, 1.f), { 0.0f, 1.0f }));
   append(create(circlePoint(180.f, 1.f), { 0.0f, 0.0f }));
   append(create(circlePoint(240.f, 1.f), { 0.0f, 0.0f }));
   append(create(circlePoint(300.f, 1.f), { 1.0f, 0.0f }));

   bindBuffer({
      0u, 1u, 2u,
      0u, 2u, 3u,
      0u, 3u, 4u,
      0u, 4u, 5u,
      0u, 5u, 6u,
      0u, 6u, 1u,
      });
   createShaders(vertex, fragment);
   createTexture(texture);
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
