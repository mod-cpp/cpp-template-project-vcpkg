#include "Blinky.hpp"

namespace pacman {

Blinky::Blinky()
  : Ghost(Atlas::Ghost::blinky, initial_position) {}

double Blinky::speed() const {
  if (state == State::Eyes)
    return 2;
  if (state == State::Frightened)
    return 0.5;
  return 0.75;
}

void Blinky::setTarget(Position pacManPos) {
  if (state == State::Eyes) {
    target = initialPosition();
    return;
  }

  if (isInPen()) {
    target = penDoorPosition();
    return;
  }

  target = state == State::Chase ? pacManPos : scatterTarget();
}

Position Blinky::initialPosition() const {
  return initial_position;
}

Position Blinky::scatterTarget() const {
  return scatter_target;
}

} // namespace pacman
