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

#include "objects/camera.hpp"
#include "objects/shape.hpp"

class GameEngine
{
public:
   GameEngine(std::string_view title);

   bool construct(int x, int y, int w, int h);

   void setWindowTitle(std::string label);

   void start();

   virtual bool createUser() = 0;
   virtual bool updateUser() = 0;

protected:
   //using Duration = std::chrono::microseconds;
   using Duration = std::chrono::milliseconds;
   using StopClock = std::chrono::steady_clock;

private:
   void OnEvent(const SDL_Event& event);
   void OnReceive();
   void OnUpdate(Duration duration);
   void OnRender();

   void initWindow();
   void initOpenGL();
   void initCamera();
   void initLights();

   void initTextures();
   void initGeometry();

   std::pair<int, int> getWindowSize();

private:
   std::string m_title;
   bool m_running{ true };
   unsigned m_frames{ 0 };

   std::vector<ogl::ShapePtr> m_shapes;
   ogl::Camera m_camera;
   ogl::Camera m_screen;

   std::chrono::time_point<StopClock> m_timer;
   std::chrono::time_point<StopClock> m_tp1;

   sdl2::sdlsystem_ptr_t m_system{ nullptr, nullptr };
   sdl2::window_ptr_t m_window{ nullptr, nullptr };
   sdl2::renderer_ptr_t m_render{ nullptr, nullptr };
};
