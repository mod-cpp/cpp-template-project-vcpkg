#include "Pinky.hpp"

namespace pacman {

Pinky::Pinky()
  : Ghost(Atlas::Ghost::pinky, initial_position) {}

double Pinky::speed() const {
  if (state == State::Eyes)
    return 2;
  if (state == State::Frightened)
    return 0.5;
  return 0.75;
}

void Pinky::setTarget(GridPosition pacManPos, Direction pacManDir) {
  if (state == State::Eyes) {
    target = initialPosition();
    return;
  }

  if (isInPen()) {
    target = penDoorPosition();
    return;
  }

  if (state == State::Scatter) {
    target = scatterTarget();
    return;
  }

  // Inky first selects a position 2 cell away from pacman in his direction.
  GridPosition targetPosition = pacManPos;
  switch (pacManDir) {
    case Direction::LEFT:
      targetPosition.x -= 4;
      break;
    case Direction::RIGHT:
      targetPosition.x += 4;
      break;
    case Direction::UP:
      targetPosition.y -= 4;
      targetPosition.x -= 4;
      break;
    case Direction::DOWN:
      targetPosition.y += 4;
      break;
    case Direction::NONE:
      assert(false && "Pacman should be moving");
      break;
  }

  target = gridPositionToPosition(targetPosition);
}

Position Pinky::initialPosition() const {
  return initial_position;
}

Position Pinky::scatterTarget() const {
  return scatter_target;
}

} // namespace pacman
