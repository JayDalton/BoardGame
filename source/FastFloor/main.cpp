#include "game.h"

auto main(int, char* []) -> int
{
   std::vector<glm::vec3> member;
   auto circlePoint = [](glm::vec2 center, float angle, float radius) -> glm::vec3
   {
      auto x = center.x + radius * std::cos(glm::radians(angle));
      auto y = center.y + radius * std::sin(glm::radians(angle));
      return glm::vec3( x, y, 0 );
   };

   float angle = 60.f;
   auto center = glm::vec3{ 0.f, 0.f, 0.f };

   member.push_back(center);
   for (int idx = 0; idx < 6; idx++)
   {
      member.push_back(circlePoint(center, idx * angle, 1.f));
   }

   FastFloor game("FastFloor");
   if (game.construct(800, 600))
   {
      game.start();
   }

   return 0;
}

