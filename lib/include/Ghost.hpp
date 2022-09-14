#pragma once

#include <chrono>

#include "Atlas.hpp"
#include "Board.hpp"
#include "Position.hpp"

namespace pacman {

struct GameState;

class Ghost {
public:
  enum class State {
    Chase,
    Scatter,
    Frightened,
    Eyes,
  };

  Ghost(Atlas::Ghost spriteSet, Position initialPosition);
  virtual ~Ghost() = default;

  GridPosition currentSprite() const;
  Position position() const;
  GridPosition positionInGrid() const;
  Direction currentDirection() const;

  void update(std::chrono::milliseconds time_delta);
  void frighten();
  void die();
  bool isFrightened() const;
  bool isEyes() const;
  void reset();

private:
  void updateAnimation(std::chrono::milliseconds time_delta);
  void updatePosition(std::chrono::milliseconds time_delta);
  void updateDirection();

protected:
  Atlas::Ghost spriteSet;
  Direction direction = Direction::NONE;
  double timeForAnimation = 0;
  std::size_t animationIndex = 0;
  State state = State::Chase;
  std::chrono::milliseconds timeFrighten = {};
  std::chrono::milliseconds timeChase = {};
  Position pos;
  Position target;
  GridPosition last_grid_position = { 0, 0 };

  State defaultStateAtDuration(std::chrono::seconds seconds);

  virtual double speed() const = 0;
  virtual Position initialPosition() const = 0;

  bool isInPen() const;
};

} // namespace pacman
