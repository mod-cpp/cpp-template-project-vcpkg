#pragma once

#include "GameState.hpp"
#include "InputState.hpp"
#include "Canvas.hpp"

namespace pacman {

class Game {
public:
  void run();

private:
  Canvas canvas;
  GameState gameState;

  void processEvents(InputState & inputState);
};

} // namespace pacman
