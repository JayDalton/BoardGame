#pragma once

#include <bitset>

#include "source/engine.h"
#include "source/shapes/shape.hpp"

class HexagonalPrism : public ogl::Shape
{
public:
   explicit HexagonalPrism(
      std::string_view vertex,
      std::string_view fragment,
      ogl::Color color
   );

   explicit HexagonalPrism(
      std::string_view vertex,
      std::string_view fragment,
      std::string_view texture
   );

   void render(ogl::Matrix position) const override;

private:
};

struct GamePlate : public ogl::Moveable
{
   std::bitset<6> n_neighbors{ 0 };

   //ogl::Matrix getPosition() const 
   //{
   //   glm::mat4 view = glm::mat4(1.0f);
   //   glm::mat4 projection = glm::mat4(1.0f);

   //   //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
   //   //model = glm::translate(model, position);
   //   view = glm::translate(view, glm::vec3(0.0f, 0.0f, -13.0f));
   //   projection = glm::perspective(
   //      glm::radians(45.0f),
   //      800.f / 600.f,          // wie funktioniert das?
   //      0.1f, 100.0f);

   //   return projection * view * ogl::Moveable::getPosition();
   //}
};

class GameModel
{
public:

   // Grid Spielfeld
   std::vector<GamePlate> m_plates;
};
