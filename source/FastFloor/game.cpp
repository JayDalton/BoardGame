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
   auto square1 = append(std::make_unique<ogl::Square>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Green));
   auto square2 = append(std::make_unique<ogl::Hexagon>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Red));
   auto square3 = append(std::make_unique<ogl::Rectangle>(ogl::SizeF{2.f,3.f}, "shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Red));

   m_cache.createHexagons(4);
   const auto member = m_cache.mapPayground(hexIcon);
   m_objects.insert(m_objects.end(), member.cbegin(), member.cend());

   //GamePlate center = m_cache.createCenter(hexIcon, {0.0f,  0.0f, 0.0f});
   //auto list = m_cache.createNeighbor(center);
   //for (auto index{ 0 }; index < 5; index++)
   //{
   //   list = m_cache.createNeighbor(list);
   //}

   //GamePlate center{ hexIcon, {0.0f,  0.0f, 0.0f}};

   //m_objects.push_back(center);
   //m_objects.push_back(center.create(GamePlate::Neighbor::Right));
   //m_objects.push_back(center.create(GamePlate::Neighbor::TopRight));
   //m_objects.push_back(center.create(GamePlate::Neighbor::TopLeft));
   //m_objects.push_back(center.create(GamePlate::Neighbor::Left));
   //m_objects.push_back(center.create(GamePlate::Neighbor::BottomLeft));
   //m_objects.push_back(center.create(GamePlate::Neighbor::BottomRight));

   //GamePlate plate{ center };
   //for (auto column{ 0 }; column < 10; column++)
   //{
   //   std::vector<GamePlate> plates{ plate };
   //   for (auto row{ 0 }; row < 10; row++)
   //   {
   //      plate = plate.create(GamePlate::Neighbor::Right);
   //      plates.push_back(plate);
   //   }

   //   plate = plates.at(0).create(GamePlate::Neighbor::BottomLeft);

   //   std::copy(plates.begin(), plates.end(), std::back_inserter(m_objects));
   //}

   //m_objects.push_back(GamePlate{ square1, {-3.0f,  -4.0f, 0.0f}});
   //m_objects.push_back(GamePlate{ square2, {00.0f,  -4.0f, 0.0f}});
   //m_objects.push_back(GamePlate{ square3, {+3.0f,  -4.0f, 0.0f}});

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
