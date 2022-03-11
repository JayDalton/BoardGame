#pragma once

#include "base/common.hpp"
#include "base/buffer.hpp"
#include "base/shader.hpp"
#include "base/texture.hpp"
#include "base/transform.hpp"

namespace ogl 
{
   struct Ident
   {
      std::int16_t m_ident{ -1 };
      auto operator<=>(const Ident&) const = default;
      explicit operator bool() const { return m_ident != -1; }
      std::size_t operator()(const Ident& k) const
      {
         return std::hash<int>()(m_ident);
      }
   };

   struct Geometry
   {
      static Vertex circlePoint(float angle, float radius)
      {
         auto x = radius * std::cos(glm::radians(angle));
         auto y = radius * std::sin(glm::radians(angle));
         return Vertex(x, y, 0);
      };
      static Vertex circlePoint(Vertex center, float angle, float radius)
      {
         auto x = center.x + radius * std::cos(glm::radians(angle));
         auto y = center.y + radius * std::sin(glm::radians(angle));
         return Vertex(x, y, center.z);
      };
      static Coords texPoint(Vertex vertex, Coords base)
      {
         return (ogl::Coords(vertex) + base) * 0.5f;
      };
   };

   struct BufferId final : public Ident {};
   struct ShaderId final : public Ident {};
   struct TextureId final : public Ident {};

   struct Drawable
   {
      BufferId m_buffer;
      ShaderId m_shader;
      TextureId m_texture1;
      TextureId m_texture2;
      Vertex m_position{ 0 };
      Matrix m_localMat{ 1.0f };

      Matrix getPosition() const
      {
         return m_localMat * glm::translate(Matrix{ 1.0f }, m_position);
      }

      void update(Duration delta)
      {
         // ???
      }
   };

   using DrawableList = std::vector<ogl::Drawable>;
}

