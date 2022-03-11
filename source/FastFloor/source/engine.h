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
   struct BufferId final : public Ident {};
   struct ShaderId final : public Ident {};
   struct TextureId final : public Ident {};

   struct Drawable
   {
      BufferId m_buffer;
      ShaderId m_shader;
      TextureId m_texture1;
      TextureId m_texture2;
      Vertex m_position{ 0 };  // raus

      unsigned m_shapeId{ 0 };

      //Matrix m_matrix{ 1.0f };
      //ogl::Color m_color{ ogl::Colors::White };

      Matrix getPosition() const
      {
         return glm::translate(Matrix{ 1.0f }, m_position);
      }

      void update(Duration delta)
      {
         // ???
      }
   };

   using DrawableList = std::vector<ogl::Drawable>;

   class GameEngine
   {
   public:
      GameEngine(std::string_view title);

      bool construct(int w, int h);

      void setWindowTitle(std::string label);

      void start();

      virtual bool createUser() = 0;
      virtual bool updateUser() = 0;


      ShaderId createShader(std::string_view vertex, std::string_view fragment);
      TextureId createTexture(std::string_view texture);

      BufferId createSquare(float radius, ogl::Color color);
      BufferId createRect(ogl::SizeF size, ogl::Color color);
      BufferId createCircle(unsigned radius, ogl::Color color);
      BufferId createHexagon(ogl::Color color);

      void render(ogl::Drawable drawable);

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

      unsigned append(ShapePtr&& shape) {
         static unsigned shapeCounter{ 100 };
         m_shapes.insert_or_assign(shapeCounter, std::move(shape));
         return shapeCounter++;
      }

      //void append(const std::vector<Drawable>& objects)
      //{
      //   m_objects.insert(m_objects.begin(), objects.cbegin(), objects.cend());
      //}

      //void append(Drawable&& objects)
      //{
      //   m_objects.push_back(objects);
      //}

      BufferId append(ogl::Buffer buffer) 
      {
         static short counter{ 200 };
         m_buffer.insert_or_assign(BufferId{ counter }, buffer);
         return BufferId{ counter++ };
      }

      //BufferId create(
      //   const std::vector<ogl::Buffer::Element>& elementList, 
      //   const std::vector<ogl::Buffer::IndexType>& indexList) 
      //{
      //   static short counter{ 200 };
      //   m_buffer.insert_or_assign(BufferId{ counter }, buffer);
      //   m_buffer.try_emplace();
      //   return BufferId{ counter++ };
      //}

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
      std::unordered_map<unsigned, ShapePtr> m_shapes;

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
