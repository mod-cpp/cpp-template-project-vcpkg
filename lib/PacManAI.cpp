#include "PacManAI.hpp"

#include "Board.hpp"
#include "Random.hpp"

namespace pacman {

void PacManAI::reset() {
  pos = {};
  suggested_direction = Direction::RIGHT;
}

// This function is not yet implemented.
// You will implement it as part of module 24.
GridPosition PacManAI::pelletClosestToPacman(GridPosition pacmanGridPosition  [[maybe_unused]],
                                             std::vector<GridPosition> & pellets [[maybe_unused]]) {
  return {0, 0};
}

// This function is not yet implemented.
// You will implement it as part of module 21.
bool PacManAI::isValidMove(const Move & move [[maybe_unused]]) {
  return false;
}

// This function is not yet implemented.
// You will implement it as part of module 21. and 24.
Direction PacManAI::optimalDirection(const std::array<Move, 4> & moves [[maybe_unused]]) {
  return Direction::NONE;
}

// This function is not yet implemented.
// You will implement it as part of module 25.
Direction PacManAI::chooseNewDirectionForPacMan(const PacMan & pacMan [[maybe_unused]],
                                               const Pellets & pellets [[maybe_unused]]) {

  const GridPosition pacManGridPos = pacMan.positionInGrid();
  auto pelletPositions = pellets.allPellets();
  if (pelletPositions.empty()) {
    return Direction::NONE;
  }

  const GridPosition targetPos = pelletClosestToPacman(pacManGridPos, pelletPositions);

  const GridPosition currentPosition = pacMan.positionInGrid();
  const auto [x, y] = currentPosition;
  std::array<Move, 4> possibleMoves = {
    Move{ Direction::UP, { x, y - 1 } },
    Move{ Direction::LEFT, { x - 1, y } },
    Move{ Direction::DOWN, { x, y + 1 } },
    Move{ Direction::RIGHT, { x + 1, y } }
  };

  for (auto & move : possibleMoves) {
    if (!isValidMove(move))
      continue;
    move.distanceToTarget = positionDistance(move.position, targetPos);
  }
  return optimalDirection(possibleMoves);
}

void PacManAI::update(const PacMan & pacMan, const Pellets & pellets [[maybe_unused]]) {

  const GridPosition pacManGridPos = pacMan.positionInGrid();
  const GridPosition currentGridPos = positionToGridPosition(pos);

  if (!isIntersection(pacManGridPos) || currentGridPos == pacManGridPos) {
    return;
  }

  suggested_direction = chooseNewDirectionForPacMan(pacMan, pellets);
  pos = pacMan.position();
}
} // namespace pacman
