#include "Position.hpp"
#include "catch2/catch.hpp"

TEST_CASE("Position are properly initialized", "[positions]") {
  pacman::Position pos;
  REQUIRE(pos.x == Approx(0.0));
  REQUIRE(pos.y == Approx(0.0));

  pacman::Position pos2{ 10.0, 20.0 };
  REQUIRE(pos2.x == Approx(10.0));
  REQUIRE(pos2.y == Approx(20.0));
}

TEST_CASE("GridPosition are properly initialized", "[positions]") {
  pacman::GridPosition gridPos{ 10, 20 };
  REQUIRE(gridPos.x == 10);
  REQUIRE(gridPos.y == 20);
}

TEST_CASE("Position converts to GridPosition", "[positions]") {
  pacman::Position pos{ 10.0, 20.0 };
  const auto gridPos = pacman::positionToGridPosition(pos);
  REQUIRE(gridPos.x == 10);
  REQUIRE(gridPos.y == 20);
}

TEST_CASE("GridPosition converts to Position", "[positions]") {
  pacman::GridPosition gridPos{ 10, 20 };
  const auto pos = pacman::gridPositionToPosition(gridPos);
  REQUIRE(pos.x == Approx(10.0));
  REQUIRE(pos.y == Approx(20.0));
}

TEST_CASE("Positions compare equal", "[positions]") {
  pacman::Position pos1{ 10.0, 20.0 };
  pacman::Position pos2{ 10.0, 20.0 };
  REQUIRE(pos1 == pos2);

  pacman::Position pos3{ 9.9, 19.9 };
  REQUIRE_FALSE(pos1 == pos3);

  pos3.x += 0.1;
  pos3.y += 0.1;

  REQUIRE(pos1 == pos3);
}
