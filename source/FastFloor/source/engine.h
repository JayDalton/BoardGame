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
#include <ranges>
#include <numeric>
#include <iostream>
#include <algorithm>

#include "imgui.h"
#include "overlay/imgui_impl_sdl.h"
#include "overlay/imgui_impl_opengl3.h"

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
      virtual bool updateUser(Matrix view) = 0;

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

      // Projektion
      glm::mat4 m_projection{ glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f) };
      //glm::mat4 m_projection{ glm::ortho(-80.0f, 80.0f, -60.0f, 60.0f, -50.0f, 100.0f) };

      // camera
      glm::vec3 m_cameraEye{ 15.0, 15.0, 15.0 };
      glm::vec3 m_cameraTarget{0.0, 0.0, 0.0};
      glm::vec3 m_cameraUpside{0.0, 0.0, 1.0};

      BufferId createSquare(float size, Color color);
      BufferId createRect(SizeF size, Color color);
      BufferId createGrid(SizeU size, Color color);

      BufferId createCircle(float size, Color color);
      BufferId createCuboid(float size, Color color);
      BufferId createSphere(float size, Color color);
      BufferId createHexagon(float size, Color color);
      BufferId createHexoid(float size, Color color);
      BufferId createCylinder(float radius, float hight, Color color);

      ShaderId createShader(std::string_view vertex, std::string_view fragment);
      TextureId createTexture(std::string_view fileName);

      void appendConsole(std::string_view text, Color color);

      void render(Drawable drawable, Matrix view);

   private:
      BufferId append(Buffer buffer) 
      {
         static short counter{ 200 };
         m_buffer.insert_or_assign(BufferId{ counter }, buffer);
         return BufferId{ counter++ };
      }

      ShaderId append(Shader shader)
      {
         static short counter{ 300 };
         m_shader.insert_or_assign(ShaderId{ counter }, shader);
         return ShaderId{ counter++ };
      }

      TextureId append(Texture texture)
      {
         static short counter{ 400 };
         m_texture.insert_or_assign(TextureId{ counter }, texture);
         return TextureId{ counter++ };
      }

      Camera m_camera;
      Camera m_screen;

      std::vector<Drawable> m_objects;
      std::unordered_map<BufferId, Buffer, Ident> m_buffer;
      std::unordered_map<ShaderId, Shader, Ident> m_shader;
      std::unordered_map<TextureId, Texture, Ident> m_texture;

      struct ConsoleText 
      {
         std::string m_text;
         ogl::Color m_color;
      };

      const std::size_t m_consoleSize{ 5 };
      std::vector<ConsoleText> m_console{
         {"Zeile mit text 1", Colors::Red},
         {"Zeile mit text 2", Colors::Red},
         {"Zeile mit text 3", Colors::Red},
      };

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

      //Size getWindowSize();

   private:
      std::string m_title;
      bool m_running{ true };
      unsigned m_frames{ 0 };

      Size m_renderSize{0, 0};
      Size m_windowSize{0, 0};

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
