#include "Game.hpp"
#include "GameState.hpp"

#include <chrono>

namespace pacman {

void Game::run() {
  const std::chrono::milliseconds delta_time(1000 / 60);
  std::chrono::milliseconds accumulator(0);
  auto current_time = std::chrono::system_clock::now();

  while (true) {
    const auto newTime = std::chrono::system_clock::now();
    const auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - current_time);

    current_time = newTime;
    accumulator += frameTime;

    processEvents(gameState.inputState);
    if (gameState.inputState.close)
      return;

    while (accumulator >= delta_time) {
      gameState.step(delta_time);
      accumulator -= delta_time;
    }

    canvas.render(gameState);
  }
}

void Game::processEvents(InputState & inputState) {
  const auto event = canvas.pollEvent();

  if (!event)
    return;

  if (event.value().type == sf::Event::Closed) {
    inputState.close = true;
    return;
  }

  if (!(event.value().type == sf::Event::KeyPressed ||
        event.value().type == sf::Event::KeyReleased))
    return;

  auto isKeyPressed = [&](sf::Keyboard::Key k) {
    bool pressed = event.value().type == sf::Event::KeyPressed;
    return k == event.value().key.code && pressed;
  };

  if (isKeyPressed(sf::Keyboard::Key::A))
    inputState.enableAI = !inputState.enableAI;

  inputState.down = isKeyPressed(sf::Keyboard::Key::Down);
  inputState.up = isKeyPressed(sf::Keyboard::Key::Up);
  inputState.left = isKeyPressed(sf::Keyboard::Key::Left);
  inputState.right = isKeyPressed(sf::Keyboard::Key::Right);
}

} // namespace pacman
