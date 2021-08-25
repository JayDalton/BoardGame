#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <memory>

#include <glm/glm.hpp>

#include "sdl2.h"

class GameEngine
{
public:
   GameEngine()
   {
   }

   bool construct(std::string_view title)
   {
      using std::cerr;
      using std::endl;

      if (auto system = sdl2::make_sdlsystem(SDL_INIT_EVERYTHING))
      {
         m_system = std::move(system);
      }
      else
      {
         cerr << "Error creating SDL2 system: " << SDL_GetError() << endl;
         return false;
      }

      if (auto win = sdl2::make_window("Hello World!", 100, 100, 620, 387, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE))
      {
         m_window = std::move(win);
      }
      else
      {
         cerr << "Error creating window: " << SDL_GetError() << endl;
         return false;
      }

      if (auto ren = sdl2::make_renderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
      {
         m_render = std::move(ren);
      }
      else
      {
         cerr << "Error creating renderer: " << SDL_GetError() << endl;
         return false;
      }

      return true;
   }

   void start()
   {
      using std::cerr;
      using std::endl;

      auto file = SDL_RWFromFile("img/grumpy-cat.bmp", "rb");
      if (file == nullptr) {
         cerr << "Error reading file: " << SDL_GetError() << endl;
         return;
      }

      auto bmp = sdl2::make_bmp(file);
      if (!bmp) {
         cerr << "Error creating surface: " << SDL_GetError() << endl;
         return;
      }

      auto tex = sdl2::make_texture(m_render.get(), bmp.get());
      if (!tex) {
         cerr << "Error creating texture: " << SDL_GetError() << endl;
         return;
      }

      SDL_Rect dest{ 50, 50, 70, 20 };

      int close = 0;
      int speed = 300;

      // annimation loop
      while (!close)
      {
         SDL_Event event;

         // Events management
         while (SDL_PollEvent(&event))
         {
            switch (event.type)
            {

            case SDL_QUIT:
               // handling of close button
               close = 1;
               break;

            case SDL_KEYDOWN:
               // keyboard API for key pressed
               switch (event.key.keysym.scancode) {
               case SDL_SCANCODE_W:
               case SDL_SCANCODE_UP:
                  dest.y -= speed / 30;
                  break;
               case SDL_SCANCODE_A:
               case SDL_SCANCODE_LEFT:
                  dest.x -= speed / 30;
                  break;
               case SDL_SCANCODE_S:
               case SDL_SCANCODE_DOWN:
                  dest.y += speed / 30;
                  break;
               case SDL_SCANCODE_D:
               case SDL_SCANCODE_RIGHT:
                  dest.x += speed / 30;
                  break;
               default:
                  break;
               }
            }
         }

         // right boundary
         if (dest.x + dest.w > 1000)
            dest.x = 1000 - dest.w;

         // left boundary
         if (dest.x < 0)
            dest.x = 0;

         // bottom boundary
         if (dest.y + dest.h > 1000)
            dest.y = 1000 - dest.h;

         // upper boundary
         if (dest.y < 0)
            dest.y = 0;

         // clears the screen
         SDL_RenderClear(m_render.get());
         SDL_RenderCopy(m_render.get(), tex.get(), nullptr, &dest);

         //SDL_SetRenderDrawColor(ren.get(), 255, 0, 0, 128);
         //SDL_RenderFillRect(ren.get(), &dest);

         // triggers the double buffers
         // for multiple rendering
         SDL_RenderPresent(m_render.get());

         // calculates to 60 fps
         SDL_Delay(1000 / 60);
      }

   }

   virtual bool createUser() = 0;
   virtual bool updateUser() = 0;

private:
   sdl2::sdlsystem_ptr_t m_system{ nullptr, nullptr };
   sdl2::window_ptr_t m_window{ nullptr, nullptr };
   sdl2::renderer_ptr_t m_render{ nullptr, nullptr };
};
