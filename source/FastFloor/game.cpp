#include "game.h"

#include "source/shapes/rectangle.hpp"


FastFloor::FastFloor(std::string_view title)
   : GameEngine(title)
{
}

bool FastFloor::createUser()
{
   auto hexBlue = append(std::make_unique<HexagonalPrism>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Blue));
   auto hexIcon = append(std::make_unique<HexagonalPrism>("shader/Complex.vs", "shader/Complex.fs", "images/container.jpg"));
   auto hexFace = append(std::make_unique<HexagonalPrism>("shader/Complex.vs", "shader/Complex.fs", "images/awesomeface.png"));

   using ogl::Geometry;

   const float pi = std::acos(-1);
   auto radius = std::cos(pi / 6) * 2;

   GamePlate center{ hexFace, {0.0f,  0.0f, 0.0f}};

   m_objects.push_back(center);
   m_objects.push_back(center.create(GamePlate::Neighbor::Right));
   m_objects.push_back(center.create(GamePlate::Neighbor::TopRight));
   m_objects.push_back(center.create(GamePlate::Neighbor::TopLeft));
   m_objects.push_back(center.create(GamePlate::Neighbor::Left));
   m_objects.push_back(center.create(GamePlate::Neighbor::BottomLeft));
   m_objects.push_back(center.create(GamePlate::Neighbor::BottomRight));


   //m_objects.push_back(GamePlate{ hexBlue, {0.0f,  0.0f, 0.0f}});
   //m_objects.push_back(GamePlate{ hexIcon, Geometry::circlePoint(000.0f, radius) });
   //m_objects.push_back(GamePlate{ hexFace, Geometry::circlePoint(060.0f, radius) });
   //m_objects.push_back(GamePlate{ hexFace, Geometry::circlePoint(120.0f, radius) });
   //m_objects.push_back(GamePlate{ hexFace, Geometry::circlePoint(180.0f, radius) });
   //m_objects.push_back(GamePlate{ hexFace, Geometry::circlePoint(240.0f, radius) });
   //m_objects.push_back(GamePlate{ hexFace, Geometry::circlePoint(300.0f, radius) });

   return true;
}

bool FastFloor::updateUser()
{
   static int counter{ 0 };

   //setWindowTitle(std::format("{:5}", counter++));




   return true;
}


// Pimpl Idiom

struct FastGame::Impl
{
   Impl() 
   {

   }
};

FastGame::FastGame()
   : m(std::make_unique<Impl>())
{

}

FastGame::~FastGame()
{
   // SDL_Quit();
}
