#include "Board.hpp"
#include "catch2/catch.hpp"

// These tests assume a static game board.

TEST_CASE("Is walkable for Pac-Man", "[board]") {
  REQUIRE_FALSE(pacman::isWalkableForPacMan(pacman::GridPosition{ 0, 0 }));   // wall
  REQUIRE_FALSE(pacman::isWalkableForPacMan(pacman::GridPosition{ 27, 0 }));  // wall
  REQUIRE_FALSE(pacman::isWalkableForPacMan(pacman::GridPosition{ 0, 30 }));  // wall
  REQUIRE_FALSE(pacman::isWalkableForPacMan(pacman::GridPosition{ 27, 30 })); // wall
  REQUIRE_FALSE(pacman::isWalkableForPacMan(pacman::GridPosition{ 11, 13 })); // pen

  REQUIRE(pacman::isWalkableForPacMan(pacman::GridPosition{ 1, 1 }));   // pellet
  REQUIRE(pacman::isWalkableForPacMan(pacman::GridPosition{ 1, 3 }));   // power pellet
  REQUIRE(pacman::isWalkableForPacMan(pacman::GridPosition{ 1, 14 }));  // nothing
  REQUIRE(pacman::isWalkableForPacMan(pacman::GridPosition{ 0, 14 }));  // portal left
  REQUIRE(pacman::isWalkableForPacMan(pacman::GridPosition{ 27, 14 })); // portal right
}

TEST_CASE("Is walkable for Ghost", "[board]") {
  const pacman::GridPosition pen = pacman::GridPosition{ 11, 13 };
  const pacman::GridPosition outside = pacman::GridPosition{ 1, 1 };

  // wall check
  REQUIRE_FALSE(pacman::isWalkableForGhost(pacman::GridPosition{ 0, 0 }, outside, false));   // wall
  REQUIRE_FALSE(pacman::isWalkableForGhost(pacman::GridPosition{ 27, 0 }, outside, false));  // wall
  REQUIRE_FALSE(pacman::isWalkableForGhost(pacman::GridPosition{ 0, 30 }, outside, false));  // wall
  REQUIRE_FALSE(pacman::isWalkableForGhost(pacman::GridPosition{ 27, 30 }, outside, false)); // wall

  // eyes can walk anywhere except walls
  REQUIRE(pacman::isWalkableForGhost(pacman::GridPosition{ 11, 13 }, outside, true)); // pen
  REQUIRE(pacman::isWalkableForGhost(pacman::GridPosition{ 1, 1 }, outside, true));   // pellet
  REQUIRE(pacman::isWalkableForGhost(pacman::GridPosition{ 1, 3 }, outside, true));   // power pellet
  REQUIRE(pacman::isWalkableForGhost(pacman::GridPosition{ 1, 14 }, outside, true));  // nothing
  REQUIRE(pacman::isWalkableForGhost(pacman::GridPosition{ 0, 14 }, outside, true));  // portal left
  REQUIRE(pacman::isWalkableForGhost(pacman::GridPosition{ 27, 14 }, outside, true)); // portal right

  // can only walk in pen if that is your origin or current location
  REQUIRE_FALSE(pacman::isWalkableForGhost(pacman::GridPosition{ 11, 13 }, outside, false)); // in pen, origin outside
  REQUIRE(pacman::isWalkableForGhost(pacman::GridPosition{ 1, 1 }, outside, false));         // outside, origin outside
  REQUIRE(pacman::isWalkableForGhost(pacman::GridPosition{ 1, 1 }, pen, false));             // outside, origin pen
  REQUIRE(pacman::isWalkableForGhost(pacman::GridPosition{ 11, 13 }, pen, false));           // in pen, origin pen
}

TEST_CASE("Is portal", "[board]") {
  const pacman::GridPosition portalRight = pacman::GridPosition{ 27, 14 };
  const pacman::GridPosition portalLeft = pacman::GridPosition{ 0, 14 };

  REQUIRE(pacman::isPortal(portalRight, pacman::Direction::RIGHT));      // right into right portal
  REQUIRE(pacman::isPortal(portalLeft, pacman::Direction::LEFT));        // left into left portal
  REQUIRE_FALSE(pacman::isPortal(portalRight, pacman::Direction::LEFT)); // left into right portal
  REQUIRE_FALSE(pacman::isPortal(portalLeft, pacman::Direction::RIGHT)); // right into left portal
}

TEST_CASE("Teleport", "[board]") {
  const pacman::GridPosition portalRight = pacman::GridPosition{ 27, 14 };
  const pacman::GridPosition portalLeft = pacman::GridPosition{ 0, 14 };

  if (pacman::isPortal(portalRight, pacman::Direction::RIGHT)) {
    const pacman::GridPosition result = pacman::teleport(portalRight);
    REQUIRE(result.x == portalLeft.x);
  }

  if (pacman::isPortal(portalLeft, pacman::Direction::LEFT)) {
    const pacman::GridPosition result = pacman::teleport(portalLeft);
    REQUIRE(result.x == portalRight.x);
  }
}