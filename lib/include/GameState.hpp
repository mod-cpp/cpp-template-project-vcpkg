#pragma once

#include "Blinky.hpp"
#include "Fruits.hpp"
#include "Ghost.hpp"
#include "Inky.hpp"
#include "InputState.hpp"
#include "PacMan.hpp"
#include "PacManAI.hpp"
#include "Pellets.hpp"
#include "Pinky.hpp"
#include "Score.hpp"
#include "SuperPellets.hpp"

namespace pacman {

struct GameState {
  void step(std::chrono::milliseconds delta);

  Blinky blinky;
  Pinky pinky;
  Inky inky;

  PacMan pacMan;
  PacManAI pacManAI;
  InputState inputState;
  Pellets pellets;
  SuperPellets superPellets;
  Fruits fruit;

  Score score;
  std::chrono::milliseconds timeSinceDeath{};

  void checkCollision(Ghost & ghost);
  void handleDeathAnimation(std::chrono::milliseconds delta);
  void eatPellets();
  void eatFruit();
  void killPacMan();
  bool isPacManDying() const;
};

} // namespace pacman
