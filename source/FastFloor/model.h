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

enum class Direction
{
   Right, Left, 
   TopRight, TopLeft,
   BottomLeft, BottomRight
};

struct GamePlate : public ogl::Moveable
{
   unsigned m_ident{ 0 };
   std::array<unsigned, 6> m_friends{ 0 };

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

};

struct PlateCache
{
   GamePlate center() const
   {

   }

   GamePlate create(GamePlate&& orig, Direction neighbor) const
   {
      auto pi = std::numbers::pi_v<float>;
      auto radius = std::cos(pi / 6) * 2;
      auto angle = getAngle(neighbor);
      auto position = ogl::Geometry::circlePoint(orig.m_position, angle, radius);
      return GamePlate{ orig.m_shapeId, position };
   }

   float getAngle(Direction direction) const
   {
      switch (direction)
      {
      case Direction::Right: return 0.f;
      case Direction::TopRight: return 60.f;
      case Direction::TopLeft: return 120.f;
      case Direction::Left: return 180;
      case Direction::BottomLeft: return 240.f;
      case Direction::BottomRight: return 300.f;
      default: return -1;
      }
   }

   std::vector<GamePlate> m_member;
};

class GameModel
{
public:

   // Grid Spielfeld
   std::vector<GamePlate> m_plates;
};
