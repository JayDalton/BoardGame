#pragma once

#include <memory>

#include "source/engine.h"

#include "model.h"

class FastFloor : public ogl::GameEngine
{
public:
   FastFloor(std::string_view title);

   bool createUser() override;
   
   bool updateUser() override;

private:
   PlateAccess m_cache;
};


struct FastGame
{
   FastGame();
   ~FastGame();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};
