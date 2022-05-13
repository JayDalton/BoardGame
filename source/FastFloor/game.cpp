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
   std::uniform_real_distribution<> distArea(-15, +15);
   std::uniform_real_distribution<> distSize(0.5, 4);
   std::uniform_real_distribution<> distColor(0, 1);

   auto square1 = createSquare(0.6, ogl::Colors::Red);
   auto square2 = createSquare(1.5, ogl::Colors::Green);
   auto rectId1 = createRect({1.5, 0.7}, ogl::Colors::Red);
   auto rectId2 = createRect({0.5, 0.7}, ogl::Colors::Blue);
   auto heagon1 = createHexagon(1.0f, ogl::Colors::Green);
   auto hexoid1 = createHexoid(1.0f, ogl::Colors::Green);

   auto circleId = createCircle(1.0f, ogl::Colors::Red);
   auto cuboidId = createCuboid(1.0f, ogl::Colors::Green);
   auto sphereId = createSphere(1.0f, ogl::Colors::Green);
   auto cyclinderId = createCylinder(1.0f, 1.f, ogl::Colors::Red);

   auto complexShader = createShader("shader/Complex.vs", "shader/Complex.fs");
   auto coloredShader = createShader("shader/Complex.vs", "shader/Colored.fs");
   auto textureId2 = createTexture("images/awesomeface.png");
   auto textureId1 = createTexture("images/container.jpg");

   //ogl::Drawable plate;
   ////plate.m_position = {3.0, 3.0, 3.0};
   ////plate.m_shader = complexShader;
   //plate.m_shader = coloredShader;
   //plate.m_texture1 = textureId1;
   //plate.m_buffer = cyclinderId;
   //m_plates.push_back(plate);

   for (auto idx{0}; idx < 15; idx++)
   {
      ogl::SizeF size{distSize(eng), distSize(eng)};
      ogl::Vertex pos{distArea(eng), distArea(eng), 0.f};
      ogl::Color color{distColor(eng), distColor(eng), distColor(eng), 1.0f};


      ogl::Drawable plate;
      plate.m_position = pos;
      plate.m_shader = coloredShader;
      //plate.m_shader = complexShader;
      plate.m_buffer = createRect(size, color);
      m_plates.push_back(plate);
   }

   return true;
}

bool FastFloor::updateUser(ogl::Matrix view)
{
   static int counter{ 0 };
   //setWindowTitle(std::format("{:5}", counter++));

   namespace clk = std::chrono;
   std::size_t objCount{ 0 };

   auto tpStart = clk::system_clock::now();
   for (auto&& object : m_plates)
   {
      if (false) // check for WorldRect.overlaps({obj.pos, obj.size})
      {
         // render only visible objects
      }
      render(object, view);
   }
   auto duration = clk::system_clock::now() - tpStart;

   appendConsole("Zeile 1", ogl::Colors::Green); // 
   appendConsole("Zeile 2", ogl::Colors::Red);
   appendConsole("Zeile 3", ogl::Colors::Green);

   //renderText("Hello World", Pos, Size, Color); // free position

   return true;
}

