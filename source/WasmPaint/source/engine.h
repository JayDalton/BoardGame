#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <filesystem>
#include <format>
#include <string>
#include <chrono>
#include <string_view>

#include "sdl2.h"

#include "objects/camera.hpp"
#include "shapes/shape.hpp"

namespace ogl
{
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
   using Duration = std::chrono::milliseconds;
   using SteadyClock = std::chrono::steady_clock;
   using TimePoint = std::chrono::time_point<SteadyClock>;
   using TimeUnit = std::chrono::nanoseconds;
   using Duration2 = std::chrono::duration<double>;

   Duration getDuration(const SteadyClock::time_point& start);

protected:

   struct MouseInfo 
   {
      bool firstMouse = true;
      float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
      float pitch = 0.0f;
      float lastX = 800.0f / 2.0;
      float lastY = 600.0 / 2.0;
      float fov = 45.0f;
   } m_mouse;

   // camera
   glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
   glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
   glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

   std::vector<ShapePtr> m_shapes;
   ogl::Camera m_camera;
   ogl::Camera m_screen;

private:
   void OnReceiveLocal();
   void OnReceiveRemote();
   
   void OnUpdateWorld(Duration duration);
   void OnRenderWorld();
   void OnRemoveWorld();

   void initWindow();
   void initOpenGL();
   void initCamera();
   void initLights();

   void initTextures();
   void initGeometry();

   //ogl::Size getWindowSize();

private:
   std::string m_title;
   bool m_running{ true };
   unsigned m_frames{ 0 };

   ogl::Size m_renderSize{0, 0};
   ogl::Size m_windowSize{0, 0};

   bool m_rendering{ true };

   // timing
   TimePoint m_lastTime{};
   TimePoint m_lastFrame{};
   TimeUnit m_deltaTime{};	// time between current frame and last frame

   void* m_context{ nullptr };
   sdl2::sdlsystem_ptr_t m_system{ nullptr, nullptr };
   sdl2::window_ptr_t m_window{ nullptr, nullptr };
   sdl2::renderer_ptr_t m_render{ nullptr, nullptr };
};

}
