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

   //auto bufferId1 = createHexagon(ogl::Colors::Red);
   auto bufferId2 = createSquare(ogl::Colors::Green);
   auto shaderId1 = createShader("shader/Complex.vs", "shader/Complex.fs");
   auto shaderId2 = createShader("shader/Complex.vs", "shader/Colored.fs");
   auto textureId1 = createTexture("images/container.jpg");
   auto textureId2 = createTexture("images/awesomeface.png");

   //auto hexBlue = append("", std::make_unique<HexagonalShape>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Blue));
   //auto hexIcon = append("", std::make_unique<HexagonalShape>("shader/Complex.vs", "shader/Complex.fs", "images/container.jpg"));
   //auto hexFace = append("", std::make_unique<HexagonalShape>("shader/Complex.vs", "shader/Complex.fs", "images/awesomeface.png"));
   auto square1 = append("", std::make_unique<ogl::Square>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Green));
   //auto square2 = append("", std::make_unique<ogl::Hexagon>("shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Red));
   //auto square3 = append("", std::make_unique<ogl::Rectangle>(ogl::SizeF{2.f,3.f}, "shader/Complex.vs", "shader/Colored.fs", ogl::Colors::Red));


   //for (auto idx{0}; idx < 3; idx++)
   //{
      //ogl::SizeF size{distSize(eng), distSize(eng)};
      //ogl::Vertex pos{distArea(eng), distArea(eng), 0.f};
      //ogl::Color color{distColor(eng), distColor(eng), distColor(eng), 1.0f};

      ogl::Drawable plate2;
      //plate2.m_position.x = distArea(eng);
      //plate2.m_position.y = distArea(eng);
      plate2.m_position.x = -2.0f;
      plate2.m_position.y = 0.0f;
      plate2.m_position.z = 0.f;
      plate2.m_texture1 = textureId2;
      plate2.m_texture2 = textureId1;
      plate2.m_shader = shaderId2;
      plate2.m_buffer = bufferId2;
      //plate2.m_shapeId = square1;
      m_plates.push_back(plate2);
      m_objects.push_back(plate2);

      ogl::Drawable plate1;
      //plate1.m_position.x = distArea(eng);
      //plate1.m_position.y = distArea(eng);
      plate1.m_position.x = +2.0f;
      plate1.m_position.y = 0.0f;
      plate1.m_position.z = 0.f;
      plate1.m_texture1 = textureId2;
      plate1.m_texture2 = textureId1;
      plate1.m_shader = shaderId2;
      plate1.m_buffer = bufferId2;
      plate1.m_shapeId = square1;
      m_plates.push_back(plate1);
      m_objects.push_back(plate1);
   //}

   //GamePlate plate{};
   //m_cache.createHexagons(4, plate);
   //const auto member = m_cache.mapPayground(plate);
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

