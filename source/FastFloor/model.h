#pragma once

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

   void render() const override;

private:
};

struct GameObject
{

};

struct GamePlate
{

};

class GameModel
{
public:

   // Grid Spielfeld
   std::vector<GamePlate> m_plates;
};
