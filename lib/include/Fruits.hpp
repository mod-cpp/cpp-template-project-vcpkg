#pragma once
#include "Position.hpp"
#include <chrono>

namespace pacman {

struct GameState;

class Fruits {
public:
  void update(std::chrono::milliseconds time_delta, int eatenPellets);

  GridPosition currentSprite() const;
  Position position() const;

  bool isVisible() const;
  int value() const;
  int eat();

private:
  bool visible = false;
  int index = 0;
  std::chrono::milliseconds time_visible{ 0 };

  void hide();
};

} // namespace pacman
