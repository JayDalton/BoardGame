#pragma once

#include <bitset>
#include <numbers>

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
   //std::bitset<6> n_neighbors{ 0 };

   enum class Neighbor : short { 
      Right = 0, TopRight = 60, TopLeft = 120, 
      Left = 180, BottomLeft = 240, BottomRight = 300
   };

   GamePlate create(Neighbor neighbor) const
   {
      auto pi = std::numbers::pi_v<float>;
      auto radius = std::cos( pi / 6) * 2;
      auto angle = static_cast<float>(neighbor);
      auto position = ogl::Geometry::circlePoint(m_position, angle, radius);
      return GamePlate{m_shapeId, position};
   }


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
