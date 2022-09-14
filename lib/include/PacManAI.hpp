#pragma once

#include "Blinky.hpp"
#include "Direction.hpp"
#include "Inky.hpp"
#include "PacMan.hpp"
#include "Pellets.hpp"
#include "Pinky.hpp"
#include "Position.hpp"
#include "SuperPellets.hpp"

namespace pacman {

class PacManAI {
public:
  struct Move {
    Direction direction = Direction::NONE;
    GridPosition position = {0, 0};
    double distanceToTarget = std::numeric_limits<double>::infinity();
  };

  void update(const PacMan & pacMan, const Pellets & pellets);
  GridPosition pelletClosestToPacman(GridPosition pacmanGridPosition,
                                     std::vector<GridPosition> & pellets);
  bool isValidMove(const Move & move);
  Direction optimalDirection(const std::array<Move, 4> & moves);
  void reset();

  Position position() const { return pos; }
  Direction direction() const { return suggested_direction; }

private:
  Direction chooseNewDirectionForPacMan(const PacMan & pacMan,
                                       const Pellets & pellets);

  Position pos = initialPacManPosition();
  Direction suggested_direction = Direction::RIGHT;
};

} // namespace pacman
