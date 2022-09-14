#pragma once
namespace pacman {

constexpr int DEFAULT_LIVES = 3;

struct Score {
  int lives = DEFAULT_LIVES;
  int points = 0;
  int eatenPellets = 0;
  int eatenFruits  = 0;
};

} // namespace pacman
