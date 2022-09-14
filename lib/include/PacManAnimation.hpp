#pragma once

#include "Atlas.hpp"
#include "Board.hpp"
#include "Direction.hpp"
#include "Position.hpp"

#include <chrono>

namespace pacman {

class PacManAnimation {
public:
  GridPosition animationFrame(Direction direction) const;
  GridPosition deathAnimationFrame() const;

  void updateAnimationPosition(std::chrono::milliseconds time_delta, bool dead);
  void pause();

private:
  size_t animation_position = 0;
  double animation_position_delta = 0.0;
};

} // namespace pacman
