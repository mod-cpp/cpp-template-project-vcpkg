#include "Blinky.hpp"
#include "Inky.hpp"
#include "Pinky.hpp"
#include "catch2/catch.hpp"

template<typename T>
static void ghostInitTest(const T & ghost, double x, double y) {
  const pacman::Position pos{ x, y };
  REQUIRE(ghost.position() == pos);

  const pacman::GridPosition gridPos = pacman::positionToGridPosition(pos);
  REQUIRE(ghost.positionInGrid() == gridPos);

  REQUIRE_FALSE(ghost.isEyes());
  REQUIRE_FALSE(ghost.isFrightened());
}

TEST_CASE("Ghosts start in the correct position", "[ghosts]") {
  pacman::Blinky blinky;
  ghostInitTest(blinky, 13.5, 11);

  pacman::Inky inky;
  ghostInitTest(inky, 13.5, 14);

  pacman::Pinky pinky;
  ghostInitTest(pinky, 11.5, 14);
}

template<typename T>
static void ghostFrightenTest(T & ghost) {
  REQUIRE_FALSE(ghost.isFrightened());
  ghost.frighten();
  REQUIRE(ghost.isFrightened());
  ghost.reset();
  REQUIRE_FALSE(ghost.isFrightened());
}

TEST_CASE("Ghosts are frighten", "[ghosts]") {
  pacman::Blinky blinky;
  ghostFrightenTest(blinky);

  pacman::Inky inky;
  ghostFrightenTest(inky);

  pacman::Pinky pinky;
  ghostFrightenTest(pinky);
}

template<typename T>
static void ghostDeadTest(T & ghost) {
  REQUIRE_FALSE(ghost.isEyes());
  ghost.die();
  REQUIRE(ghost.isEyes());
  ghost.reset();
  REQUIRE_FALSE(ghost.isEyes());
}

TEST_CASE("Ghosts can die", "[ghosts]") {
  pacman::Blinky blinky;
  ghostDeadTest(blinky);

  pacman::Inky inky;
  ghostDeadTest(inky);

  pacman::Pinky pinky;
  ghostDeadTest(pinky);
}
