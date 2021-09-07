#include "game.h"

auto main(int, char* []) -> int
{
   // Pimpl
   FastGame fast;


   FastFloor game("FastFloor");
   if (game.construct(800, 600))
   {
      game.start();
   }

   return 0;
}

