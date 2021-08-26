#pragma once

#include "engine.h"

class FastFloor : public GameEngine
{
public:
   FastFloor(std::string_view title);

   bool createUser() override;
   
   bool updateUser() override;

private:
};
