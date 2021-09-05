#pragma once

#include "source/engine.h"

#include "model.h"

class FastFloor : public ogl::GameEngine
{
public:
   FastFloor(std::string_view title);

   bool createUser() override;
   
   bool updateUser() override;

private:

   // Grid Spielfeld
   // 
   GameModel m_model;
};
