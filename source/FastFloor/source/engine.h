#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <filesystem>
#include <format>
#include <iostream>
#include <string>
#include <chrono>
#include <string_view>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>

#include "sdl2.h"

#include "objects/camera.hpp"
#include "shapes/shape.hpp"

namespace ogl 
{
   //auto getDuration = [](const StopClock::time_point& start) {
   //   return std::chrono::duration_cast<Duration>(StopClock::now() - start);
   //};
};

class GameEngine
{
public:
   GameEngine(std::string_view title);

   bool construct(int w, int h);

   void setWindowTitle(std::string label);

   void start();

   virtual bool createUser() = 0;
   virtual bool updateUser() = 0;

protected:
   //using Duration = std::chrono::microseconds;
   using Duration = std::chrono::milliseconds;
   using StopClock = std::chrono::steady_clock;

   Duration getDuration(const StopClock::time_point& start);

private:
   void OnReceiveLocal();
   void OnReceiveServer();
   
   void OnUpdateWorld(Duration duration);
   void OnRenderWorld();

   void initWindow();
   bool initOpenGL();
   void initCamera();
   void initLights();

   unsigned loadShader(std::string_view vertex, std::string_view fragment);
   void initTextures();
   void initGeometry();

   std::pair<int, int> getWindowSize();

private:
   std::string m_title;
   bool m_running{ true };
   unsigned m_frames{ 0 };

   bool m_rendering{ true };

   struct MouseInfo 
   {
      bool firstMouse = true;
      float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
      float pitch = 0.0f;
      float lastX = 800.0f / 2.0;
      float lastY = 600.0 / 2.0;
      float fov = 45.0f;
   } m_mouse;

   // timing
   float m_deltaTime = 0.0f;	// time between current frame and last frame
   float m_lastFrame = 0.0f;

   // camera
   glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
   glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
   glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

   std::vector<ogl::ShapePtr> m_shapes;
   ogl::Camera m_camera;
   ogl::Camera m_screen;

   std::chrono::time_point<StopClock> m_timer;
   std::chrono::time_point<StopClock> m_tp1;

   void* m_context{ nullptr };
   sdl2::sdlsystem_ptr_t m_system{ nullptr, nullptr };
   sdl2::window_ptr_t m_window{ nullptr, nullptr };
   sdl2::renderer_ptr_t m_render{ nullptr, nullptr };
};
