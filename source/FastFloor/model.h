#pragma once

#include <bitset>
#include <numbers>

#include "source/engine.h"
#include "source/shapes/shape.hpp"

class HexagonalPrism : public ogl::Shape
{
public:
   explicit HexagonalPrism(
      std::string_view vertex,
      std::string_view fragment,
      ogl::Color color
   );

   explicit HexagonalPrism(
      std::string_view vertex,
      std::string_view fragment,
      std::string_view texture
   );

   void render(ogl::Matrix position) const override;

private:
};

enum class Direction
{
   Right, Left, 
   TopRight, TopLeft,
   BottomLeft, BottomRight
};

struct HexCoord
{
   const std::int32_t q{ 0 }, r{ 0 }, s{ 0 };
   auto operator<=>(const HexCoord&) const = default;
   explicit operator bool() const { return q + r + s == 0; }

   HexCoord add(HexCoord a) const {
      return HexCoord(a.q + q, a.r + r, a.s + s);
   }

   HexCoord subtract(HexCoord a) const {
      return HexCoord(a.q - q, a.r - r, a.s - s);
   }

   HexCoord multiply(HexCoord a, int k) const {
      return HexCoord(a.q * k, a.r * k, a.s * k);
   }

   int length() const {
      return int((std::abs(q) + std::abs(r) + std::abs(s)) / 2);
   }

   int distance(HexCoord a) const {
      return a.subtract(*this).length();
   }

   // www.redblobgames.com/grids/hexagons/implementation.html
   std::size_t operator()(const HexCoord& k) const
   {
      const auto hq = std::hash<int>()(q);
      const auto hr = std::hash<int>()(r);
      return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
   }
};

using HexMap = std::unordered_map<HexCoord, float, HexCoord, HexCoord>;
using HexSet = std::unordered_set<HexCoord, HexCoord>;

//int hex_length(Hex hex) {
//   return int((abs(hex.q) + abs(hex.r) + abs(hex.s)) / 2);
//}
//
//int hex_distance(Hex a, Hex b) {
//   return hex_length(hex_subtract(a, b));
//}

struct GamePlate : public ogl::Moveable
{
   unsigned m_ident{ 0 };
   std::array<unsigned, 6> m_friends{ 0 };

   static const inline std::unordered_map<Direction, float> m_sideMap
   {
      {Direction::Right, 0.0f}, {Direction::TopRight, 60.0f},
      {Direction::TopLeft, 120.0f}, {Direction::Left, 180.0f},
      {Direction::BottomLeft, 240.0f}, {Direction::BottomRight, 300.0f},
   };


   bool hasNeighbor(Direction dir) const
   {
      return m_friends.at(static_cast<unsigned>(dir)) != 0;
   }

   unsigned getNeighbor(Direction dir) const
   {
      return m_friends.at(static_cast<unsigned>(dir));
   }

   void setNeighbor(Direction dir, unsigned ident)
   {
      m_friends[static_cast<unsigned>(dir)] = ident;
   }

   enum class Neighbor : short { 
      Right = 0, TopRight = 60, TopLeft = 120, 
      Left = 180, BottomLeft = 240, BottomRight = 300
   };

   GamePlate create(Neighbor neighbor) const
   {
      auto pi = std::numbers::pi_v<float>;
      auto radius = std::cos( pi / 6) * 2;
      auto angle = static_cast<float>(neighbor);
      auto position = ogl::Geometry::circlePoint(m_position, angle, radius);
      return GamePlate{m_shapeId, position};
   }

};

struct PlateAccess
{
   std::unordered_map<Direction, HexCoord> m_hexDirection{
      {Direction::Right, HexCoord{1, 0, -1}},
      {Direction::TopRight, HexCoord{1, -1, 0}},
      {Direction::TopLeft, HexCoord{0, -1, 1}}, 
      {Direction::Left, HexCoord{-1, 0, 1}},
      {Direction::BottomLeft, HexCoord{-1, 1, 0}}, 
      {Direction::BottomRight, HexCoord{0, 1, -1}},
   };

   HexCoord get_neighbor(HexCoord hex, Direction direction) 
   {
      return hex.add(m_hexDirection.at(direction));
   }

   struct Layout {
      const glm::vec2 scale{ 1, 1 };
      const glm::vec2 origin{ 0, 0 };
      const glm::mat2x2 orientation{ 
         std::sqrt(3.0), std::sqrt(3.0) / 2.0, 
         0.0, 3.0 / 2.0 };
   };

   ogl::Vertex hex_to_pixel(Layout layout, HexCoord h) 
   {
      glm::vec2 v1 = layout.orientation[0];
      glm::vec2 v2 = layout.orientation[1];

      auto x = (v1.x * h.q + v1.y * h.r) * layout.scale.x;
      auto y = (v2.x * h.q + v2.y * h.r) * layout.scale.y;
      return { x + layout.origin.x, y + layout.origin.y, 0 };
   }

   //FractionalHex pixel_to_hex(Layout layout, ogl::Vertex p) 
   //{
   //   const Orientation& M = layout.orientation;
   //   ogl::Vertex pt = ogl::Vertex(
   //      (p.x - layout.origin.x) / layout.size.x,
   //      (p.y - layout.origin.y) / layout.size.y,
   //      0);
   //   double q = M.b0 * pt.x + M.b1 * pt.y;
   //   double r = M.b2 * pt.x + M.b3 * pt.y;
   //   return FractionalHex(q, r, -q - r);
   //}

   //ogl::Vertex hex_corner_offset(Layout layout, Direction corner) 
   //{
   //   auto size = layout.size;
   //   auto pi = std::numbers::pi_v<float>;
   //   auto cornerInt = static_cast<int>(corner);
   //   double angle = 2.0 * pi * (layout.orientation.start_angle + cornerInt) / 6;
   //   return ogl::Vertex(size.x * std::cos(angle), size.y * std::sin(angle), 0);
   //}

   void createParallelograms(int fromX, int toX, int fromY, int toY)
   {
      m_hexSet.clear();
      for (int q = fromX; q <= toX; q++) {
         for (int r = fromY; r <= toY; r++) {
            m_hexSet.insert(HexCoord(q, r, -q - r));
         }
      }
   }

   void createTriangles(int size)
   {
      m_hexSet.clear();
      for (int q = 0; q <= size; q++) {
         for (int r = 0; r <= size - q; r++) {
            m_hexSet.insert(HexCoord(q, r, -q - r));
         }
      }
   }

   void createHexagons(int radius)
   {
      m_hexSet.clear();
      for (int q = -radius; q <= radius; q++) 
      {
         int r1 = std::max(-radius, -q - radius);
         int r2 = std::min( radius, -q + radius);
         for (int r = r1; r <= r2; r++) 
         {
            m_hexSet.insert(HexCoord(q, r, -q - r));
         }
      }
   }

   std::vector<GamePlate> mapPayground(unsigned shapeId)
   {
      std::vector<GamePlate> result;
      result.reserve(m_hexSet.size());

      for (auto&& hex : m_hexSet)
      {
         auto position = hex_to_pixel(Layout{}, hex);
         result.push_back(create(shapeId, position));
      }

      return result;
   }

   const std::vector<GamePlate>& getMember() const
   {
      return m_member;
   }

   unsigned nextPlateIdent()
   {
      return ++m_plateCounter;
   }

   const GamePlate& append(unsigned shapeId, ogl::Vertex position)
   {
      auto ident{ nextPlateIdent() };
      //m_member.insert_or_assign(ident, GamePlate{ shapeId, position, ident});
      return m_member.emplace_back(GamePlate{ shapeId, position, ident});
   }

   GamePlate create(unsigned shapeId, ogl::Vertex position)
   {
      auto ident{ nextPlateIdent() };
      return GamePlate{ shapeId, position, ident};
   }

   const GamePlate& append(const GamePlate& plate, Direction direction)
   {
      auto position = getNewPosition(plate.m_position, direction);
      return m_member.emplace_back(GamePlate{ plate.m_shapeId, position, m_plateCounter++ });
   }

   void createHexagonalArea(unsigned shape, int level)
   {
      std::vector<GamePlate> input{ append(shape, {0.0f,  0.0f, 0.0f}) };

      for (auto index{ 0 }; index < level; index++)
      {
         input = createNeighbour(input);
      }
   }

   std::vector<GamePlate> createNeighbour(std::vector<GamePlate> plates)
   {
      std::vector<GamePlate> result;
      for (auto plate : plates)
      {
         for (auto&& [side, angle] : plate.m_sideMap)
         {
            if (!plate.hasNeighbor(side))
            {
               auto posi = getNewPosition(plate.m_position, side);
               auto next = create(plate.m_shapeId, posi);
               //plate.setNeighbor(side, next.m_ident);
               next.setNeighbor(side, plate.m_ident);
               result.push_back(next);
            }
         }
         result.push_back(plate);
      }

      for (const auto& plate : result)
      {
      }

      return result;
   }

private:
   ogl::Vertex getNewPosition(const ogl::Vertex& vertex, Direction side)
   {
      auto pi = std::numbers::pi_v<float>;
      auto radius = std::cos(pi / 6) * 2;
      return ogl::Geometry::circlePoint(vertex, getAngle(side), radius);
   }

   float getAngle(Direction direction) const
   {
      switch (direction)
      {
      case Direction::Right: return 0.f;
      case Direction::TopRight: return 60.f;
      case Direction::TopLeft: return 120.f;
      case Direction::Left: return 180;
      case Direction::BottomLeft: return 240.f;
      case Direction::BottomRight: return 300.f;
      default: return -1;
      }
   }

   unsigned m_plateCounter{ 1001 };
   std::vector<GamePlate> m_member;
   //std::unordered_map<unsigned, GamePlate> m_member;

   HexMap m_hexMap;
   HexSet m_hexSet;
};

class GameModel
{
public:

   // Grid Spielfeld
   std::vector<GamePlate> m_plates;
};
