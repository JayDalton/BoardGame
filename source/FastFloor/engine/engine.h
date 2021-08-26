#pragma once

#include <iostream>
#include <memory>
#include <format>
#include <format>
#include <iostream>
#include <string>
#include <chrono>
#include <string_view>

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>

#include "sdl2.h"

class GameEngine
{
public:
   GameEngine(std::string_view title);

   bool construct(int x, int y, int w, int h);

   void setWindowTitle(std::string label);

   void start();

   virtual bool createUser() = 0;
   virtual bool updateUser() = 0;

private:
   std::string m_title;
   std::chrono::time_point<std::chrono::steady_clock> m_tp1;
   std::chrono::time_point<std::chrono::steady_clock> m_tp2;

   sdl2::sdlsystem_ptr_t m_system{ nullptr, nullptr };
   sdl2::window_ptr_t m_window{ nullptr, nullptr };
   sdl2::renderer_ptr_t m_render{ nullptr, nullptr };
};
