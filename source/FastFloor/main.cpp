#include "game.h"

auto main(int, char* []) -> int
{
   FastFloor game("FastFloor");
   if (game.construct(640, 480))
   {
      game.start();
   }

   return 0;
}

