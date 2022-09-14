#pragma once

#include "Board.hpp"
#include "Position.hpp"

namespace pacman {

class Pellets {
public:
  Pellets();

  GridPosition currentSprite() const {
    return sprite;
  };

  std::vector<GridPosition> allPellets() const {
    return positions;
  }

  bool isPellet(GridPosition p) const;
  bool eatPelletAtPosition(GridPosition p);

private:
  const GridPosition sprite = { 1, 9 };
  std::vector<GridPosition> positions;
};

} // namespace pacman
