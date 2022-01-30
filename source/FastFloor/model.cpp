#include "model.h"

HexagonalPrism::HexagonalPrism(std::string_view vertex, 
   std::string_view fragment, ogl::Color color)
{
   append(create(ogl::Vertex{ 0.f }, color));
   append(create(circlePoint(030.f, 1.f), color));
   append(create(circlePoint(090.f, 1.f), color));
   append(create(circlePoint(150.f, 1.f), color));
   append(create(circlePoint(210.f, 1.f), color));
   append(create(circlePoint(270.f, 1.f), color));
   append(create(circlePoint(330.f, 1.f), color));

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

HexagonalPrism::HexagonalPrism(std::string_view vertex, 
   std::string_view fragment, std::string_view texture)
{
   ogl::Coords texBase(-1.0f, -1.0f);

   append(create(ogl::Vertex{ 0.f }, { 0.5f, 0.5f }));
   append(create(texBase, circlePoint(000.f, 1.f)));
   append(create(texBase, circlePoint(060.f, 1.f)));
   append(create(texBase, circlePoint(120.f, 1.f)));
   append(create(texBase, circlePoint(180.f, 1.f)));
   append(create(texBase, circlePoint(240.f, 1.f)));
   append(create(texBase, circlePoint(300.f, 1.f)));

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

void HexagonalPrism::render() const
{
   // bind textures on corresponding texture units
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, Texture::m_id);
   //glActiveTexture(GL_TEXTURE1);
   //glBindTexture(GL_TEXTURE_2D, Texture::m_id2);

   // render container
   Shader::useShader();

   ogl::Vertex cubePositions[] = {
      ogl::Vertex(0.0f,  0.0f, 0.0f),
      ogl::Vertex(2.0f,  2.0f, 0.0f),
      ogl::Vertex(4.0f,  2.0f, 0.0f),
      ogl::Vertex(4.0f,  4.0f, 0.0f),
   };

   for (const auto& pos : cubePositions)
   {
      // create transformations
      glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
      glm::mat4 view = glm::mat4(1.0f);
      glm::mat4 projection = glm::mat4(1.0f);

      //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
      model = glm::translate(model, pos);
      view = glm::translate(view, glm::vec3(0.0f, 0.0f, -13.0f));
      projection = glm::perspective(
         glm::radians(45.0f), 
         800.f / 600.f,          // wie funktioniert das?
         0.1f, 100.0f);

      Shader::setMat4("projection", projection);
      Shader::setMat4("model", model);
      Shader::setMat4("view", view);

      glBindVertexArray(m_VAO);
      glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
   }
}


