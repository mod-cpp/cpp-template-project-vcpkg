#include "Inky.hpp"

namespace pacman {

Inky::Inky()
  : Ghost(Atlas::Ghost::inky, initial_position) {}

double Inky::speed() const {
  if (state == State::Eyes)
    return 2;
  if (state == State::Frightened)
    return 0.5;
  return 0.75;
}

void Inky::setTarget(GridPosition pacManPos, Direction pacManDir, GridPosition blinkyPos) {
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
      targetPosition.x -= 2;
      break;
    case Direction::RIGHT:
      targetPosition.x += 2;
      break;
    case Direction::UP:
      targetPosition.y -= 2;
      targetPosition.x -= 2;
      break;
    case Direction::DOWN:
      targetPosition.y += 2;
      break;
    case Direction::NONE:
      assert(false && "Pacman should be moving");
      break;
  }

  // Then it calculates the distance between Blinky and this position
  const double distanceBetweenBlinkyAndTarget = std::hypot(blinkyPos.x - targetPosition.x, blinkyPos.y - targetPosition.y);

  // And selects a point on the line crossing blinky and
  // this position that is at twice that distance away from blinky
  targetPosition.x += std::size_t((double(targetPosition.x) - double(blinkyPos.x)) / distanceBetweenBlinkyAndTarget) * 2;
  targetPosition.y += std::size_t((double(targetPosition.y) - double(blinkyPos.y)) / distanceBetweenBlinkyAndTarget) * 2;

  target = gridPositionToPosition(targetPosition);
}

Position Inky::initialPosition() const {
  return initial_position;
}

Position Inky::scatterTarget() const {
  return scatter_target;
}

} // namespace pacman
