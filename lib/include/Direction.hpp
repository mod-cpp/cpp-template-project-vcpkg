#pragma once

namespace pacman {

enum class Direction {
  NONE,
  LEFT,
  RIGHT,
  UP,
  DOWN
};

inline Direction oppositeDirection(Direction d) {
  switch (d) {
    case Direction::LEFT:
      return Direction::RIGHT;
    case Direction::RIGHT:
      return Direction::LEFT;
    case Direction::UP:
      return Direction::DOWN;
    case Direction::DOWN:
      return Direction::UP;
    case Direction::NONE:
      return d;
  }
  return d;
}

} // namespace pacman
