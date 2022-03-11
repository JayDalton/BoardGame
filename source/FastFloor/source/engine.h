#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <filesystem>
#include <format>
#include <string>
#include <chrono>
#include <string_view>
#include <unordered_set>
#include <unordered_map>

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
      virtual bool updateUser(ogl::Matrix view) = 0;

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
      glm::vec3 m_cameraPosition = glm::vec3(0.0, -15.0, 15.0);
      glm::vec3 m_cameraTarget = glm::vec3(0.0, 0.0, 0.0);
      glm::vec3 m_cameraUpside = glm::vec3(0.0, 0.0, 1.0);

      BufferId createSquare(float radius, ogl::Color color);
      BufferId createRect(ogl::SizeF size, ogl::Color color);
      BufferId createCircle(unsigned radius, ogl::Color color);
      BufferId createHexagon(ogl::Color color);

      ShaderId createShader(std::string_view vertex, std::string_view fragment);
      TextureId createTexture(std::string_view texture);

      void render(ogl::Drawable drawable, ogl::Matrix view);

   private:
      BufferId append(ogl::Buffer buffer) 
      {
         static short counter{ 200 };
         m_buffer.insert_or_assign(BufferId{ counter }, buffer);
         return BufferId{ counter++ };
      }

      ShaderId append(ogl::Shader shader)
      {
         static short counter{ 300 };
         m_shader.insert_or_assign(ShaderId{ counter }, shader);
         return ShaderId{ counter++ };
      }

      TextureId append(ogl::Texture shader)
      {
         static short counter{ 400 };
         m_texture.insert_or_assign(TextureId{ counter }, shader);
         return TextureId{ counter++ };
      }

      ogl::Camera m_camera;
      ogl::Camera m_screen;

      std::vector<Drawable> m_objects;
      std::unordered_map<BufferId, Buffer, Ident> m_buffer;
      std::unordered_map<ShaderId, Shader, Ident> m_shader;
      std::unordered_map<TextureId, Texture, Ident> m_texture;

   private:
      void OnReceiveLocal();
      void OnReceiveRemote();
   
      void OnUpdateWorld(Duration duration);
      void OnRenderWorld(Duration duration);
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
      Duration m_deltaTime{};	// time between current frame and last frame

      void* m_context{ nullptr };
      sdl2::sdlsystem_ptr_t m_system{ nullptr, nullptr };
      sdl2::window_ptr_t m_window{ nullptr, nullptr };
      sdl2::renderer_ptr_t m_render{ nullptr, nullptr };
   };

}
