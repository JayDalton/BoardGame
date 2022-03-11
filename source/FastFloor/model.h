#pragma once

#include <bitset>
#include <numbers>

#include "source/engine.h"
#include "source/shapes/shape.hpp"

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
   // www.redblobgames.com/grids/hexagons/implementation.html

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

   std::size_t operator()(const HexCoord& k) const
   {
      const auto hq = std::hash<int>()(q);
      const auto hr = std::hash<int>()(r);
      return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
   }
};

struct Layout 
{
   const glm::vec2 scale{ 1, 1 };
   const glm::vec2 origin{ 0, 0 };
   const glm::mat2x2 orientation{ 
      std::sqrt(3.0), std::sqrt(3.0) / 2.0, 
      0.0, 3.0 / 2.0 };
};

struct GamePlate : public ogl::Drawable
{
   HexCoord m_hex{};
};

struct PlateAccess
{
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

   auto calculateHexagonPosition(int radius)
   {
      std::vector<ogl::Vertex> result;
      for (int q = -radius; q <= radius; q++) 
      {
         int r1 = std::max(-radius, -q - radius);
         int r2 = std::min( radius, -q + radius);
         for (int r = r1; r <= r2; r++) 
         {
            HexCoord hex{ q, r, -q - r };
            auto pos = hex_to_pixel(Layout{}, hex);
            result.push_back(pos);
         }
      }
      return result;
   }

protected:
   HexCoord get_neighbor(HexCoord hex, Direction direction)
   {
      return hex.add(m_hexDirection.at(direction));
   }

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

   std::unordered_map<Direction, HexCoord> m_hexDirection{
      {Direction::Right, HexCoord{1, 0, -1}},
      {Direction::TopRight, HexCoord{1, -1, 0}},
      {Direction::TopLeft, HexCoord{0, -1, 1}},
      {Direction::Left, HexCoord{-1, 0, 1}},
      {Direction::BottomLeft, HexCoord{-1, 1, 0}},
      {Direction::BottomRight, HexCoord{0, 1, -1}},
   };


private:
   unsigned m_plateCounter{ 1001 };

   using HexMap = std::unordered_map<HexCoord, GamePlate, HexCoord>;
   using HexSet = std::unordered_set<HexCoord, HexCoord>;

   HexMap m_hexMap;
   HexSet m_hexSet;
};

