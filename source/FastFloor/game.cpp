#include "game.h"

#include "source/shapes/rectangle.hpp"


FastFloor::FastFloor(std::string_view title)
   : GameEngine(title)
{
}

bool FastFloor::createUser()
{
   auto hexBlue = append(std::make_unique<HexagonalShape>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Blue));
   auto hexIcon = append(std::make_unique<HexagonalShape>("shader/Complex.vs", "shader/Complex.fs", "images/container.jpg"));
   auto hexFace = append(std::make_unique<HexagonalShape>("shader/Complex.vs", "shader/Complex.fs", "images/awesomeface.png"));
   auto square1 = append(std::make_unique<ogl::Square>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Green));
   auto square2 = append(std::make_unique<ogl::Hexagon>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Red));
   auto square3 = append(std::make_unique<ogl::Rectangle>(ogl::SizeF{2.f,3.f}, "shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Red));

   //m_cache.createParallelograms(0, 4, 0, 3);
   //m_cache.createTriangles(4);
   m_cache.createHexagons(4);
   const auto member = m_cache.mapPayground(hexFace);
   m_objects.insert(m_objects.end(), member.cbegin(), member.cend());


   return true;
}

bool FastFloor::updateUser()
{
   static int counter{ 0 };

   //setWindowTitle(std::format("{:5}", counter++));


   return true;
}

