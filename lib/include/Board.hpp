#pragma once

#include "Direction.hpp"
#include "Position.hpp"
#include <array>
#include <cstdint>
#include <vector>

namespace pacman {

bool isWalkableForPacMan(GridPosition point);
bool isWalkableForGhost(GridPosition target_position, GridPosition current_position, bool isEyes);
bool isInPen(GridPosition point);
bool isPortal(GridPosition point, Direction direction);
bool isIntersection(GridPosition point);

GridPosition teleport(GridPosition point);

std::vector<GridPosition> initialPelletPositions();
std::vector<GridPosition> initialSuperPelletPositions();

inline Position penDoorPosition() {
  return { 13, 11 };
}
inline Position initialPacManPosition() {
  return { 13.5, 23 };
}

} // namespace pacman
