#include "Board.hpp"

namespace pacman {

const std::size_t ROWS = 31;
const std::size_t COLUMNS = 28;

enum class Cell {
  wall = 0,
  pellet = 1,
  // nothing = 2,
  // missing 3,
  power_pellet = 4,
  pen = 5,
  left_portal = 6,
  right_portal = 7
};

// clang-format off
constexpr std::array<std::array<int, COLUMNS>, ROWS> board = {{
 // 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 0
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, // 1
  { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 }, // 2
  { 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 4, 0 }, // 3
  { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 }, // 4
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, // 5
  { 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0 }, // 6
  { 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0 }, // 7
  { 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0 }, // 8
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, // 9
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, // 10
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, // 11
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 5, 5, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, // 12
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 5, 5, 5, 5, 5, 5, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, // 13
  { 6, 2, 2, 2, 2, 2, 1, 2, 2, 2, 0, 5, 5, 5, 5, 5, 5, 0, 2, 2, 2, 1, 2, 2, 2, 2, 2, 7 }, // 14
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 5, 5, 5, 5, 5, 5, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, // 15
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, // 16
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, // 17
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, // 18
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0 }, // 19
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, // 20
  { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 }, // 21
  { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 }, // 22
  { 0, 4, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 4, 0 }, // 23
  { 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0 }, // 24
  { 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0 }, // 25
  { 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0 }, // 26
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, // 27
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, // 28
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, // 29
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 30
}};
// clang-format on

static Cell cellAtPosition(GridPosition point) {
  if (point.x >= COLUMNS || point.y >= ROWS)
    return Cell::wall;
  return Cell(board[point.y][point.x]);
}

bool isWalkableForPacMan(GridPosition point) {
  return cellAtPosition(point) != Cell::wall && cellAtPosition(point) != Cell::pen;
}

bool isWalkableForGhost(GridPosition target_position, GridPosition current_position, bool isEyes) {
  const Cell cell = cellAtPosition(target_position);
  if (cell == Cell::wall)
    return false;
  return isEyes || isInPen(current_position) || !isInPen(target_position);
}

bool isInPen(GridPosition point) {
  return cellAtPosition(point) == Cell::pen;
}

bool isPortal(GridPosition point, Direction direction) {
  return (cellAtPosition(point) == Cell::left_portal && direction == Direction::LEFT) ||
         (cellAtPosition(point) == Cell::right_portal && direction == Direction::RIGHT);
}

bool isIntersection(GridPosition point) {
  if (!isWalkableForPacMan(point) || cellAtPosition(point) == Cell::left_portal || cellAtPosition(point) == Cell::right_portal) {
    return false;
  }

  const GridPosition right{ point.x + 1, point.y };
  const bool rightWalkable = isWalkableForPacMan(right);

  const GridPosition left{ point.x - 1, point.y };
  const bool leftWalkable = isWalkableForPacMan(left);

  const GridPosition top{ point.x, point.y - 1 };
  const bool topWalkable = isWalkableForPacMan(top);

  const GridPosition bottom{ point.x, point.y + 1 };
  const bool bottomWalkable = isWalkableForPacMan(bottom);

  return (topWalkable && rightWalkable) || (rightWalkable && bottomWalkable) || (bottomWalkable && leftWalkable) || (leftWalkable && topWalkable);
}

GridPosition teleport(GridPosition point) {
  size_t right = COLUMNS - 1;
  size_t left = 0;
  if (point.x == left)
    point.x = right;
  else if (point.x == right)
    point.x = left;
  return point;
}

std::vector<GridPosition> initialPelletPositions() {
  std::vector<GridPosition> positions;

  for (std::size_t row = 0; row < ROWS; row++) {
    for (std::size_t column = 0; column < COLUMNS; column++) {
      if (board[row][column] == int(Cell::pellet))
        positions.emplace_back(column, row);
    }
  }
  return positions;
}

std::vector<GridPosition> initialSuperPelletPositions() {
  std::vector<GridPosition> positions;

  positions.reserve(4); // Reserve space for 4 super pellets

  for (std::size_t row = 0; row < ROWS; row++) {
    for (std::size_t column = 0; column < COLUMNS; column++) {
      if (board[row][column] == int(Cell::power_pellet))
        positions.emplace_back(column, row);
    }
  }
  return positions;
}

} // namespace pacman
