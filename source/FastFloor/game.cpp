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

   auto bufferId = createHexagon(ogl::Colors::Red);
   auto shaderId1 = createShader("shader/Complex.vs", "shader/Complex.fs");
   auto shaderId2 = createShader("shader/Complex.vs", "shader/Colored.fs");
   auto textureId1 = createTexture("images/container.jpg");
   auto textureId2 = createTexture("images/awesomeface.png");

   for (auto idx{0}; idx < 1; idx++)
   {
      ogl::SizeF size{distSize(eng), distSize(eng)};
      ogl::Vertex pos{distArea(eng), distArea(eng), 0.f};
      ogl::Color color{distColor(eng), distColor(eng), distColor(eng), 1.0f};

      ogl::Drawable plate;
      //plate.m_position.x = distArea(eng);
      //plate.m_position.y = distArea(eng);
      plate.m_position.x = 0.5f;
      plate.m_position.y = 0.5f;
      plate.m_texture1 = textureId2;
      plate.m_texture2 = textureId1;
      plate.m_shader = shaderId1;
      plate.m_buffer = bufferId;
      m_plates.push_back(plate);
   }

   //auto hexBlue = append("", std::make_unique<HexagonalShape>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Blue));
   //auto hexIcon = append("", std::make_unique<HexagonalShape>("shader/Complex.vs", "shader/Complex.fs", "images/container.jpg"));
   //auto hexFace = append("", std::make_unique<HexagonalShape>("shader/Complex.vs", "shader/Complex.fs", "images/awesomeface.png"));
   //auto square1 = append("", std::make_unique<ogl::Square>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Green));
   //auto square2 = append("", std::make_unique<ogl::Hexagon>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Red));
   //auto square3 = append("", std::make_unique<ogl::Rectangle>(ogl::SizeF{2.f,3.f}, "shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Red));

   ////m_cache.createParallelograms(0, 4, 0, 3);
   ////m_cache.createTriangles(4);

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

   for (auto&& object : m_plates)
   {
      render(object);
   }

   return true;
}

