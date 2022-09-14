#pragma once

#include <cassert>
#include <cmath>
#include <limits>

namespace pacman {

struct Position {
  double x = 0.0;
  double y = 0.0;
};

struct GridPosition {
  size_t x;
  size_t y;
  constexpr GridPosition(size_t x, size_t y)
    : x(x),
      y(y) {}
};

inline GridPosition positionToGridPosition(Position pos) {
  assert(pos.x >= 0 && pos.y >= 0 && "Position should have positive values");
  return { size_t(std::round(pos.x)), size_t(std::round(pos.y)) };
}

inline Position gridPositionToPosition(GridPosition pos) {
  return { double(pos.x), double(pos.y) };
}

constexpr bool operator==(const GridPosition & a, const GridPosition & b) {
  return a.x == b.x && a.y == b.y;
}

constexpr bool operator!=(const GridPosition & a, const GridPosition & b) {
  return !(a == b);
}

template<typename T>
inline double positionDistance(const T & a, const T & b) {
  const double first = double(a.x) - double(b.x);
  const double second = double(a.y) - double(b.y);
  return std::sqrt((first * first) + (second * second));
}

inline bool operator==(const Position & a, const Position & b) {
  // This is ok as a test unless x and y become very large.
  constexpr double epsilon = std::numeric_limits<double>::epsilon();
  return std::abs(a.x - b.x) <= epsilon && std::abs(a.y - b.y) <= epsilon;
}

inline bool operator!=(const Position & a, const Position & b) {
  return !(a == b);
}

} // namespace pacman
