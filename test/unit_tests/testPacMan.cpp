#include "PacMan.hpp"
#include "catch2/catch.hpp"

TEST_CASE("Pacman has the correct initial position") {
  pacman::PacMan pacMan;
  REQUIRE(pacMan.position().x == 13.5);
  REQUIRE(pacMan.position().y == 23);
}
