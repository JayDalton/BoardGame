#include "game.h"
#include <random>

#include "source/shapes/rectangle.hpp"


FastFloor::FastFloor(std::string_view title)
   : GameEngine(title)
{
}

bool FastFloor::createUser()
{
   std::random_device rd;
   std::mt19937 eng(rd());
   std::uniform_real_distribution<> distArea(-3, +3);
   std::uniform_real_distribution<> distSize(0.3, 0.7);
   std::uniform_real_distribution<> distColor(0, 255);

   auto bufferId1 = createHexagon(ogl::Colors::Red);
   auto bufferId2 = createSquare(ogl::SizeF{0.7f, 0.4f}, ogl::Colors::Blue);
   auto shaderId1 = createShader("shader/Complex.vs", "shader/Complex.fs");
   auto shaderId2 = createShader("shader/Complex.vs", "shader/Colored.fs");
   auto textureId1 = createTexture("images/container.jpg");
   auto textureId2 = createTexture("images/awesomeface.png");

   for (auto idx{0}; idx < 3; idx++)
   {
      ogl::SizeF size{distSize(eng), distSize(eng)};
      ogl::Vertex pos{distArea(eng), distArea(eng), 0.f};
      ogl::Color color{distColor(eng), distColor(eng), distColor(eng), 1.0f};

      ogl::Drawable plate;
      plate.m_position.x = distArea(eng);
      plate.m_position.y = distArea(eng);
      //plate.m_position.x = 0.0f;
      //plate.m_position.y = 0.0f;
      plate.m_texture1 = textureId2;
      plate.m_texture2 = textureId1;
      plate.m_shader = shaderId2;
      plate.m_buffer = bufferId2;
      m_plates.push_back(plate);
      m_objects.push_back(plate);
   }

   //GamePlate plate{};
   //m_cache.createHexagons(4, plate);
   //const auto member = m_cache.mapPayground(hexFace);
   //m_objects.insert(m_objects.end(), member.cbegin(), member.cend());

   return true;
}

bool FastFloor::updateUser()
{
   static int counter{ 0 };

   //setWindowTitle(std::format("{:5}", counter++));

   //for (auto&& object : m_plates)
   //{
   //   render(object);
   //}

   return true;
}

