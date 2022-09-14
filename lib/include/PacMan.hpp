#pragma once

#include "Direction.hpp"
#include "PacManAnimation.hpp"
#include "Position.hpp"

#include <chrono>

namespace pacman {

class PacMan {
public:
  GridPosition currentSprite() const;
  Position position() const;
  GridPosition positionInGrid() const;

  void update(std::chrono::milliseconds time_delta, Direction input_direction);

  void die();
  void reset();
  bool hasDirection() const {
    return direction != Direction::NONE;
  }

  Direction currentDirection() const {
    return direction;
  }

private:
  Direction direction = Direction::NONE;
  Direction desired_direction = Direction::NONE;
  Position pos = initialPacManPosition();
  PacManAnimation pacManAnimation;
  bool dead = false;

  void updateAnimationPosition(std::chrono::milliseconds time_delta, bool paused);
  void updateMazePosition(std::chrono::milliseconds time_delta);
};

} // namespace pacman
