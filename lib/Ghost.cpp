#include "Ghost.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>

namespace pacman {

Ghost::Ghost(Atlas::Ghost spriteSet, Position initialPosition)
  : spriteSet(spriteSet),
    pos(initialPosition) {
}

void Ghost::frighten() {
  if (state > State::Scatter)
    return;

  direction = oppositeDirection(direction);
  state = State::Frightened;
  timeFrighten = {};
}

bool Ghost::isFrightened() const {
  return state == State::Frightened;
}

bool Ghost::isEyes() const {
  return state == State::Eyes;
}

void Ghost::die() {
  if (state == State::Eyes)
    return;

  direction = oppositeDirection(direction);
  state = State::Eyes;
  timeFrighten = {};
  timeChase = {};
}

void Ghost::reset() {
  pos = initialPosition();
  state = State::Scatter;
  timeFrighten = {};
  timeChase = {};
}

GridPosition Ghost::currentSprite() const {
  switch (state) {
    default:
      return Atlas::ghostSprite(spriteSet, direction, (animationIndex % 2) == 0);
    case State::Eyes:
      return Atlas::eyeSprite(direction);
    case State::Frightened:
      if (timeFrighten.count() < 3500)
        return Atlas::initialFrightened(animationIndex);
      else
        return Atlas::endingFrightened(animationIndex);
  }
}

Position Ghost::position() const {
  return pos;
}

GridPosition Ghost::positionInGrid() const {
  return positionToGridPosition(pos);
}

Direction Ghost::currentDirection() const {
  return direction;
}

void Ghost::update(std::chrono::milliseconds time_delta) {
  if (state == State::Eyes && isInPen())
    state = State::Scatter;

  if (state == State::Frightened) {
    timeFrighten += time_delta;
    if (timeFrighten.count() > 6000)
      state = State::Scatter;
  }

  if (state == State::Scatter || state == State::Chase) {
    timeChase += time_delta;
    const auto newState = defaultStateAtDuration(std::chrono::duration_cast<std::chrono::seconds>(timeChase));
    if (newState != state) {
      direction = oppositeDirection(direction);
      state = newState;
    }
  }

  updateAnimation(time_delta);
  updatePosition(time_delta);
}

bool Ghost::isInPen() const {
  return pacman::isInPen(positionInGrid());
}

void Ghost::updatePosition(std::chrono::milliseconds time_delta) {
  updateDirection();

  double position_delta = (0.004 * double(time_delta.count())) * speed();

  const auto old_position = pos;
  const GridPosition old_grid_position = positionToGridPosition(old_position);

  switch (direction) {
    case Direction::NONE:
      break;
    case Direction::LEFT:
      pos.x -= position_delta;
      pos.y = round(pos.y);
      break;
    case Direction::RIGHT:
      pos.x += position_delta;
      pos.y = round(pos.y);
      break;
    case Direction::UP:
      pos.x = round(pos.x);
      pos.y -= position_delta;
      break;
    case Direction::DOWN:
      pos.x = round(pos.x);
      pos.y += position_delta;
      break;
  }

  if (isPortal(positionInGrid(), direction)) {
    pos = gridPositionToPosition(teleport(positionInGrid()));
  } else if (!isWalkableForGhost(positionInGrid(), old_grid_position, isEyes())) {
    pos = old_position;
    direction = oppositeDirection(direction);
  }
}

/*
 *  Each time a ghost finds itself at an intersection,
 *  it picks a target position - the specific target depends on the state
 *  of the ghost and the specific ghost.
 *
 *  For each 4 cells around the current ghost position the straight-line distance
 *  to the target is calculated (this ignores all obstacles, including walls)
 *
 *  The ghost then selects among these 4 cells the one with the shortest euclidean distance to the target.
 *  If a cell is a wall or would cause a ghost to move in the opposite direction, the distance to the target
 *  from that cell is considered infinite (due to the shape of the maze, there is always one direction
 *  a ghost can take).
 *
 *  In the scatter state, each ghost tries to reach an unreachable position outside of the map.
 *  This makes ghosts run in circle around the island at each of the 4 map corner.
 */
void Ghost::updateDirection() {
  const auto current_grid_position = positionInGrid();
  if (current_grid_position == last_grid_position)
    return;

  struct Move {
    Direction direction = Direction::NONE;
    Position position;
    double distance_to_target = std::numeric_limits<double>::infinity();
  };

  const auto x = double(current_grid_position.x);
  const auto y = double(current_grid_position.y);

  std::array<Move, 4> possible_moves = {
    Move{ Direction::UP, { x, y - 1 } },
    Move{ Direction::LEFT, { x - 1, y } },
    Move{ Direction::DOWN, { x, y + 1 } },
    Move{ Direction::RIGHT, { x + 1, y } }
  };

  for (auto & move : possible_moves) {
    if (isPortal(current_grid_position, move.direction))
      move.position = gridPositionToPosition(teleport(current_grid_position));

    const bool invalid_position = (move.position.x < 0 || move.position.y < 0);
    if (invalid_position)
      continue;

    const bool opposite_direction = (move.direction == oppositeDirection(direction));
    if (opposite_direction)
      continue;

    const GridPosition grid_position = { size_t(move.position.x), size_t(move.position.y) };
    const bool can_walk = isWalkableForGhost(grid_position, current_grid_position, isEyes());
    if (!can_walk)
      continue;

    move.distance_to_target = std::hypot(move.position.x - target.x, move.position.y - target.y);
  }

  const auto optimal_move = std::min_element(possible_moves.begin(), possible_moves.end(), [](const auto & a, const auto & b) {
    return a.distance_to_target < b.distance_to_target;
  });

  const auto & move = *optimal_move;
  direction = move.direction;
  last_grid_position = current_grid_position;
}

void Ghost::updateAnimation(std::chrono::milliseconds time_delta) {
  timeForAnimation += double(time_delta.count());
  if (timeForAnimation >= 250) {
    timeForAnimation = 0;
    animationIndex = (animationIndex + 1) % 4;
  }
}

/*
 *  Ghosts alternate between the scatter and chase states at
 *  specific intervals
 */
Ghost::State Ghost::defaultStateAtDuration(std::chrono::seconds seconds) {
  // This array denotes the duration of each state, alternating between scatter and chase
  std::array changes = { /*scatter*/ 7, 20, 7, 20, 5, 20, 5 };

  // To know the current state we first compute the cumulative time using std::partial_sum
  // This gives us {7, 27, 34, 54, 59, 79, 84}
  std::partial_sum(std::begin(changes), std::end(changes), std::begin(changes));

  // Then we look for the first value in the array greater than the time spent in chase/scatter states
  auto it = std::upper_bound(std::begin(changes), std::end(changes), seconds.count());

  // We get the position of that iterator in the array
  auto count = std::distance(std::begin(changes), it);

  // Because the first position is scatter, all the even positions will be "scatter"
  // all the odd positions will be "chase"
  return count % 2 == 0 ? State::Scatter : State::Chase;
}

} // namespace pacman
