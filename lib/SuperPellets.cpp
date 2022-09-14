#include "SuperPellets.hpp"
#include <algorithm>

namespace pacman {

SuperPellets::SuperPellets()
  : positions(initialSuperPelletPositions()) {}

bool SuperPellets::isPellet(GridPosition p) const {
  auto match = [&p](GridPosition pellet) {
    return p.x == pellet.x && p.y == pellet.y;
  };

  return std::any_of(positions.begin(), positions.end(), match);
}

bool SuperPellets::eatPelletAtPosition(GridPosition p) {
  auto it = std::find(positions.begin(), positions.end(), p);
  if (it == positions.end())
    return false;
  positions.erase(it);
  return true;
}

} // namespace pacman
