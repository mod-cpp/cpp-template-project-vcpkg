#include "Pellets.hpp"
#include <algorithm>

namespace pacman {

Pellets::Pellets()
  : positions(initialPelletPositions()) {}

bool Pellets::isPellet(GridPosition p) const {
  for(const GridPosition & position : positions) {
      if(position == p)
          return true;
  }
  return false;
}

bool Pellets::eatPelletAtPosition(GridPosition p) {
    for(auto it = positions.begin(); it != positions.end(); ++it) {
        if(*it == p) {
            positions.erase(it);
            return true;
        }
    }
    return false;
}

} // namespace pacman
