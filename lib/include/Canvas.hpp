#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.hpp"
#include "Position.hpp"
#include <optional>

namespace pacman {

using Rect = sf::Rect<int>;
using Sprite = sf::Sprite;

class Canvas {
public:
  Canvas();
  void render(const GameState & gameState);
  std::optional<sf::Event> pollEvent();

private:
  static constexpr uint16_t LEFT_MARGIN = 40 * 2;
  static constexpr uint16_t TOP_MARGIN = 40 * 2;
  static constexpr uint16_t BOTTOM_MARGIN = 40 * 2;
  static constexpr uint16_t MAZE_WIDTH = 448;
  static constexpr uint16_t MAZE_HEIGHT = 496;
  static constexpr uint16_t MAZE_SCALE_UP = 2;
  static constexpr uint16_t TARGET_MAZE_WIDTH = 448 * MAZE_SCALE_UP;
  static constexpr uint16_t TARGET_MAZE_HEIGHT = 496 * MAZE_SCALE_UP;
  static constexpr uint16_t SCORE_WIDTH = 200 * 2;
  static constexpr uint16_t SPRITE_WIDTH = 32;
  static constexpr uint16_t SPRITE_HEIGHT = 32;

  void clear();
  void render();
  void renderMaze();
  void renderPacMan(const PacMan & pac_man);
  void renderGhost(const Ghost & ghost);
  void renderPellets(const Pellets & pellets);
  void renderSuperPellets(const SuperPellets & superPellets);
  void renderFruits(const Fruits& fruit, int eatenFruits);

  void renderScore(int score);
  void renderLives(int lives);

  void renderSprite(Sprite sprite, Position pos);
  static Rect viewDimensions();
  static sf::Texture loadTexture(std::string_view path);
  static sf::Font loadFont(std::string_view path);

  Sprite getSprite(GridPosition rect) const;

  sf::RenderWindow window;
  sf::View view;
  sf::Texture maze_texture;
  sf::Texture sprites_texture;
  sf::Font game_font;
};

} // namespace pacman
