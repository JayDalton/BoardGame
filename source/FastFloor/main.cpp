#include "game.h"

auto main(int, char* []) -> int
{
   FastFloor game("FastFloor");
   if (game.construct(800, 600))
   {
      game.start();
   }

   return 0;
}

