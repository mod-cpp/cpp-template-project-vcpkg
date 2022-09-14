#pragma once

#include "Direction.hpp"
#include "Position.hpp"
#include <cassert>

#include <array>

namespace pacman::Atlas {

enum class Ghost : unsigned int {
  blinky = 2,
  pinky = 3,
  inky = 4,
  clyde = 5,
};

constexpr GridPosition pacman_right_wide = { 0, 0 };
constexpr GridPosition pacman_right_narrow = { 1, 0 };
constexpr GridPosition pacman_closed = { 2, 0 };
constexpr GridPosition pacman_left_narrow = { 3, 0 };
constexpr GridPosition pacman_left_wide = { 4, 0 };
constexpr GridPosition pacman_up_wide = { 5, 0 };
constexpr GridPosition pacman_up_narrow = { 6, 0 };
constexpr GridPosition pacman_down_wide = { 7, 0 };
constexpr GridPosition pacman_down_narrow = { 8, 0 };

constexpr GridPosition ghost_blue_frightened = { 0, 7 };
constexpr GridPosition ghost_blue_frightened2 = { 1, 7 };
constexpr GridPosition ghost_white_frightened = { 2, 7 };
constexpr GridPosition ghost_white_frightened2 = { 3, 7 };

constexpr GridPosition eyeSprite(Direction direction) {
  switch (direction) {
    case Direction::RIGHT:
      return { 0, 6 };
    case Direction::DOWN:
      return { 2, 6 };
    case Direction::LEFT:
      return { 4, 6 };
    case Direction::UP:
      return { 6, 6 };
    default:
      return { 0, 6 };
  }
}

constexpr GridPosition ghostSprite(Ghost ghost, Direction direction, bool alternative) {
  assert(ghost >= Ghost::blinky && ghost <= Ghost::clyde && "Invalid Ghost");
  auto y = static_cast<size_t>(ghost);
  size_t x = 0;
  switch (direction) {
    case Direction::RIGHT:
      x = 0;
      break;
    case Direction::DOWN:
      x = 2;
      break;
    case Direction::LEFT:
      x = 4;
      break;
    case Direction::UP:
      x = 6;
      break;
    default:
      x = 0;
      break;
  }
  if (alternative)
    x++;
  return { x, y };
}

constexpr GridPosition initialFrightened(std::size_t animationIndex) {
  return (animationIndex % 2) == 0 ? Atlas::ghost_blue_frightened2 : Atlas::ghost_blue_frightened;
}

constexpr GridPosition endingFrightened(std::size_t animationIndex) {
  std::array<GridPosition, 4> positions = { Atlas::ghost_blue_frightened,
                                            Atlas::ghost_blue_frightened2,
                                            Atlas::ghost_white_frightened,
                                            Atlas::ghost_white_frightened2 };
  return positions[animationIndex];
}
} // namespace pacman::Atlas
