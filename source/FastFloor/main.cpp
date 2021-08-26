#include "game.h"

auto main(int, char* []) -> int
{
   FastFloor game("FastFloor");
   if (game.construct(100, 100, 620, 387))
   {
      game.start();
   }

   return 0;
}

