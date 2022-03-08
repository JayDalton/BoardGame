#include "model.h"

HexagonalShape::HexagonalShape(std::string_view vertex, 
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

HexagonalShape::HexagonalShape(std::string_view vertex, 
   std::string_view fragment, std::string_view texture)
{
   ogl::Coords texBase(-1.0f, -1.0f);

   append(create(ogl::Vertex{ 0.f }, { 0.5f, 0.5f }));
   append(create(texBase, circlePoint(030.f, 1.f)));
   append(create(texBase, circlePoint(090.f, 1.f)));
   append(create(texBase, circlePoint(150.f, 1.f)));
   append(create(texBase, circlePoint(210.f, 1.f)));
   append(create(texBase, circlePoint(270.f, 1.f)));
   append(create(texBase, circlePoint(330.f, 1.f)));

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

void HexagonalShape::render(ogl::Matrix model) const
{
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, Texture::id());

   // render container
   Shader::useShader();
   Shader::setMat4("model", model);

   glBindVertexArray(m_VAO);
   glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}


