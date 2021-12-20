
#include <cstdio>

//#include "source/sdl2.h"
////#include <emscripten.h>
//
//SDL_Surface* screen;
//
//void drawRandomPixels() {
//   if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
//
//   Uint8* pixels = screen->pixels;
//
//   for (int i = 0; i < 1048576; i++) {
//      char randomByte = rand() % 255;
//      pixels[i] = randomByte;
//}
//
//   if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
//
//      (screen);
//}
//
//int main(int argc, char* argv[]) {
//   SDL_Init(SDL_INIT_VIDEO);
//   screen = SDL_SetVideoMode(512, 512, 32, SDL_SWSURFACE);
//
//   emscripten_set_main_loop(drawRandomPixels, 60, 1);
//}

auto main(int, char* []) -> int
{
   printf("hello, world!\n");
   return 0;
}

