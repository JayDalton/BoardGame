#include "game.h"

#include "source/shapes/rectangle.hpp"


FastFloor::FastFloor(std::string_view title)
   : GameEngine(title)
{
}

bool FastFloor::createUser()
{
   //m_shapes.push_back(
   //   std::make_unique<ogl::Hexagon>(
   //      "shader/Simple.vs",
   //      "shader/Simple.fs",
   //      ogl::Colors::Green));

   m_shapes.push_back(
      std::make_unique<HexagonalPrism>(
         "shader/Simple.vs",
         "shader/Simple.fs",
         ogl::Colors::Green));


   return true;
}

bool FastFloor::updateUser()
{
   static int counter{ 0 };

   //setWindowTitle(std::format("{:5}", counter++));

   return true;
}
