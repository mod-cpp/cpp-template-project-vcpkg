#include "Canvas.hpp"
#include "Scaling.hpp"
#include <fmt/format.h>
#include <string>
#include <vector>

namespace pacman {

Canvas::Canvas()
  : window(sf::VideoMode(std::uint32_t(viewDimensions().width / 2), std::uint32_t(viewDimensions().height / 2)),
           "Pacman",
           sf::Style::Titlebar | sf::Style::Close),
    view(sf::FloatRect(0, 0, float(viewDimensions().width), float(viewDimensions().height))) {

  window.setView(view);
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  // We render the game in view at twice the native resolution,
  // Then project it on a scaled window - on some mac we get the
  // scaling factor of the window to adjust the resolution
  const auto scale = scaling_factor_for_window(window.getSystemHandle());
  const auto width = (viewDimensions().width / 2.0) * scale;
  const auto height = (viewDimensions().height / 2.2) * scale;
  window.setSize(sf::Vector2u(unsigned(width), unsigned(height)));

  maze_texture = loadTexture("maze.png");
  sprites_texture = loadTexture("sprites32.png");
  game_font = loadFont("retro_font.ttf");
}

void Canvas::render(const GameState & gameState) {
  clear();

  renderMaze();
  renderPellets(gameState.pellets);
  renderSuperPellets(gameState.superPellets);

  renderGhost(gameState.blinky);
  renderGhost(gameState.pinky);
  renderGhost(gameState.inky);

  renderScore(gameState.score.points);
  renderLives(gameState.score.lives);

  renderFruits(gameState.fruit, gameState.score.eatenFruits);

  renderPacMan(gameState.pacMan);

  render();
}

void Canvas::clear() {
  window.clear(sf::Color::Black);
}

void Canvas::render() {
  window.display();
}

std::optional<sf::Event> Canvas::pollEvent() {
  sf::Event event{};
  if (window.pollEvent(event))
    return event;
  return std::nullopt;
}

void Canvas::renderMaze() {
  Sprite maze;
  maze.setTexture(maze_texture);
  maze.setTextureRect(sf::IntRect{
    0,
    0,
    MAZE_WIDTH,
    MAZE_HEIGHT });
  maze.setScale(MAZE_SCALE_UP, MAZE_SCALE_UP);
  maze.setPosition(LEFT_MARGIN, TOP_MARGIN);
  window.draw(maze);
}

void Canvas::renderPellets(const Pellets & pellets) {
  Sprite pellet = getSprite(pellets.currentSprite());
  std::vector<GridPosition> pelletPositions = pellets.allPellets();
  for (const auto & pos : pelletPositions) {
    renderSprite(pellet, gridPositionToPosition(pos));
  }
}

void Canvas::renderSuperPellets(const SuperPellets & superPellets) {
  Sprite pellet = getSprite(superPellets.currentSprite());
  std::vector<GridPosition> superPelletPositions = superPellets.allPellets();
  for (const auto & pos : superPelletPositions) {
    renderSprite(pellet, gridPositionToPosition(pos));
  }
}

void Canvas::renderPacMan(const PacMan & pac_man) {
  Sprite pacmanSprite = getSprite(pac_man.currentSprite());
  const auto & pos = pac_man.position();
  renderSprite(pacmanSprite, pos);
}

void Canvas::renderFruits(const Fruits & fruit, int eatenFruits) {
  Sprite sprite = getSprite(fruit.currentSprite());
  if (fruit.isVisible()) {
    const auto & pos = fruit.position();
    renderSprite(sprite, pos);
  }

  const auto x = static_cast<size_t>(LEFT_MARGIN + TARGET_MAZE_WIDTH + LEFT_MARGIN);
  const auto y = static_cast<size_t>((TARGET_MAZE_HEIGHT / 3.0) * 2);

  for (auto i = 0; i < eatenFruits + 1; i++) {
    const auto sprite_position = float(i) * SPRITE_WIDTH * 1.5f;
    const sf::Vector2f pos{ x + sprite_position, y };
    sprite.setPosition(pos.x, pos.y);

    window.draw(sprite);
  }
}

void Canvas::renderGhost(const Ghost & ghost) {
  Sprite sprite = getSprite(ghost.currentSprite());
  const auto & pos = ghost.position();
  renderSprite(sprite, pos);
}

void Canvas::renderScore(int score) {
  const int x = (LEFT_MARGIN + TARGET_MAZE_WIDTH + LEFT_MARGIN);
  const int y = (TOP_MARGIN * 2);

  sf::Text text;
  text.setPosition(x, y);
  text.setFont(game_font);
  text.setString(fmt::format("SCORE\n{}", score));
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::White);
  window.draw(text);
}

void Canvas::renderLives(int lives) {
  constexpr GridPosition liveSprite = Atlas::pacman_left_narrow;
  const size_t x = (LEFT_MARGIN + TARGET_MAZE_WIDTH + LEFT_MARGIN);
  const size_t y = TARGET_MAZE_HEIGHT;

  Sprite pacmanSprite = getSprite(liveSprite);
  for (auto i = 0; i < lives - 1; i++) {
    auto life_position = float(i) * SPRITE_WIDTH * 1.5f;
    sf::Vector2f pos{ x + life_position, y };
    pacmanSprite.setPosition(pos.x, pos.y);
    window.draw(pacmanSprite);
  }
}

Rect Canvas::viewDimensions() {
  const double width = (LEFT_MARGIN + TARGET_MAZE_WIDTH + SCORE_WIDTH);
  const double height = (TOP_MARGIN + TARGET_MAZE_HEIGHT + BOTTOM_MARGIN);
  return { 0, 0, int(width), int(height) };
}

Sprite Canvas::getSprite(GridPosition coordinate) const {
  sf::Sprite sprite;
  sprite.setTexture(sprites_texture);
  sprite.setTextureRect(sf::IntRect{ int(coordinate.x * SPRITE_WIDTH),
                                     int(coordinate.y * SPRITE_HEIGHT),
                                     SPRITE_WIDTH,
                                     SPRITE_HEIGHT });
  return sprite;
}

void Canvas::renderSprite(Sprite sprite, Position pos) {
  pos.x = LEFT_MARGIN + (pos.x * SPRITE_WIDTH);
  pos.y = TOP_MARGIN + (pos.y * SPRITE_HEIGHT);
  sprite.setPosition(float(pos.x), float(pos.y));
  window.draw(sprite);
}

static void exitFailure(const std::string & message) {
  fmt::print("{}\n", message);
  exit(1);
}

sf::Texture Canvas::loadTexture(std::string_view path) {
  sf::Texture texture;
  if (!texture.loadFromFile(std::string{ path })) {
    exitFailure(fmt::format("Failed to load image {}", path));
  }
  return texture;
}

sf::Font Canvas::loadFont(std::string_view path) {
  sf::Font font;
  if (!font.loadFromFile(std::string{ path })) {
    exitFailure(fmt::format("Failed to load font {}", path));
  }
  return font;
}

} // namespace pacman
