#pragma once

#include <memory>
#include <vector>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <format>
#include <numbers>
#include <variant>
#include <unordered_map>
#include <unordered_set>

#include <filesystem>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <GL/glew.h>

namespace ogl
{
   //using Size = glm::u32vec2;
   using SizeF = glm::vec2;
   using Color = glm::vec4;
   using Vertex = glm::vec3;
   using Coords = glm::vec2;
   using Matrix = glm::mat4;

   //using Duration = std::chrono::milliseconds;
   using Duration = std::chrono::duration<float>;
   using SteadyClock = std::chrono::steady_clock;
   using TimePoint = std::chrono::time_point<SteadyClock>;
   using TimeUnit = std::chrono::nanoseconds;

   struct Size
   {
      std::int32_t x{ 0 }, y{ 0 };
      auto operator<=>(const Size&) const = default;
   };

   struct SizeU
   {
      std::uint32_t x{ 0 }, y{ 0 };
      auto operator<=>(const SizeU&) const = default;
   };

   struct Colors {
      static constexpr Color White{ 1.0f, 1.0f, 1.0f, 1.0f };
      static constexpr Color Black{ 0.0f, 0.0f, 0.0f, 1.0f };
      static constexpr Color Red{ 1.0f, 0.0f, 0.0f, 1.0f };
      static constexpr Color Green{ 0.0f, 1.0f, 0.0f, 1.0f };
      static constexpr Color Blue{ 0.0f, 0.0f, 1.0f, 1.0f };
      static constexpr Color Grey{ 0.5f, 0.5f, 0.5f, 1.0f };
      static constexpr Color Silver{ 0.6f, 0.6f, 0.6f, 1.0f };
   };
}
