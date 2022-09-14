#include "Fruits.hpp"
#include "GameState.hpp"
#include "catch2/catch.hpp"

TEST_CASE("Fruit default initialization", "[fruits]") {
  pacman::Fruits fruit;
  REQUIRE_FALSE(fruit.isVisible());
  REQUIRE(fruit.value() == 100);
  REQUIRE(fruit.currentSprite().x == 3);
  REQUIRE(fruit.currentSprite().y == 8);
  REQUIRE(fruit.position().x == Approx(13.5));
  REQUIRE(fruit.position().y == Approx(17));
}

TEST_CASE("Fruit Visibility", "[fruits]") {
  pacman::GameState gameState;
  REQUIRE_FALSE(gameState.fruit.isVisible());

  SECTION("9 seconds but no pellets eaten") {
    gameState.fruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.fruit.isVisible());
  }

  SECTION("9 seconds and 70 pellets eaten") {
    // "Eat 70 pellets", do an update and check the state
    gameState.score.eatenPellets = 70;
    gameState.fruit.update(std::chrono::milliseconds(1), gameState.score.eatenPellets);
    REQUIRE(gameState.fruit.isVisible());

    // Wait more than 9 seconds and then check the state again
    gameState.fruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.fruit.isVisible());
  }

  SECTION("70 and 170 pellets eaten") {
    // "Eat 70 pellets", do an update and check the state
    gameState.score.eatenPellets = 70;
    gameState.fruit.update(std::chrono::milliseconds(1), gameState.score.eatenPellets);
    REQUIRE(gameState.fruit.isVisible());

    // Wait more than 9 seconds and then check the state again
    gameState.fruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.fruit.isVisible());

    // "Eat 170 pellets", do an update and check the state
    gameState.score.eatenPellets = 170;
    gameState.fruit.update(std::chrono::milliseconds(1), gameState.score.eatenPellets);
    REQUIRE(gameState.fruit.isVisible());

    // Wait more than 9 seconds and then check the state again
    gameState.fruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.fruit.isVisible());

    // We should never get a visible state again, since we only show 2 fruits
    gameState.score.eatenPellets = 1000;
    gameState.fruit.update(std::chrono::milliseconds(1), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.fruit.isVisible());

    // Wait more than 9 seconds and then check the state again
    gameState.fruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.fruit.isVisible());
  }

  SECTION("Eating a fruit") {
    REQUIRE(gameState.fruit.eat() == 0);

    gameState.score.eatenPellets = 70;
    gameState.fruit.update(std::chrono::milliseconds(1), gameState.score.eatenPellets);
    REQUIRE(gameState.fruit.isVisible());
    REQUIRE(gameState.fruit.eat() == gameState.fruit.value());

    // Wait more than 9 seconds and then check the state again
    gameState.fruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.fruit.isVisible());
    REQUIRE(gameState.fruit.eat() == 0);
  }
}