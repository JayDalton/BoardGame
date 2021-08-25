#include "game.h"

auto main(int, char* []) -> int
{
   FastFloor game;
   if (game.construct("Hello!"))
   {
      game.start();
   }

   return 0;
}

