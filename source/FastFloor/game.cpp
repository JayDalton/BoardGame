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

   //auto hexBlue = create<HexagonalPrism>(
   //      "shader/Complex.vs",
   //      "shader/Colored.fs",
   //      ogl::Colors::Blue);

   m_shapes.push_back(
      std::make_unique<HexagonalPrism>(
         "shader/Complex.vs",
         "shader/Colored.fs",
         ogl::Colors::Blue));

   //m_shapes.push_back(
   //   std::make_unique<HexagonalPrism>(
   //      "shader/Complex.vs",
   //      "shader/Complex.fs",
   //      "images/container.jpg"));

   //m_shapes.push_back(
   //   std::make_unique<HexagonalPrism>(
   //      "shader/Complex.vs",
   //      "shader/Complex.fs",
   //      "images/awesomeface.png"));

   //Vertex{}
   GamePlate;

   //m_model.m_plates.push_back();

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
