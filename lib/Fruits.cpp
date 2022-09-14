#include "Fruits.hpp"
#include "GameState.hpp"

namespace pacman {

void Fruits::update(std::chrono::milliseconds time_delta, int eatenPellets) {
  if (visible) {
    time_visible += time_delta;
  }

  if (time_visible > std::chrono::seconds(9)) {
    hide();
  } else if ((index == 0 && eatenPellets >= 70) || (index == 1 && eatenPellets >= 170)) {
    // We show the fruit twice, once at 70 pellets and once at 170
    visible = true;
  }
}

GridPosition Fruits::currentSprite() const {
  // That's the cherry
  return { 3, 8 };
}

Position Fruits::position() const {
  // under the pen
  return { 13.5, 17 };
}

bool Fruits::isVisible() const {
  return visible;
}

int Fruits::value() const {
  // The cherry is worth 100
  return 100;
}

int Fruits::eat() {
  if (!isVisible()) {
    return 0;
  }

  hide();
  return value();
}

void Fruits::hide() {
  index++;
  time_visible = std::chrono::seconds{ 0 };
  visible = false;
}

} // namespace pacman
