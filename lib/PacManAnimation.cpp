#include "PacManAnimation.hpp"

namespace pacman {

constexpr std::array<GridPosition,4> down_animation { Atlas::pacman_down_wide, Atlas::pacman_down_narrow, Atlas::pacman_closed, Atlas::pacman_down_narrow };
constexpr std::array<GridPosition,4> left_animation{ Atlas::pacman_left_wide, Atlas::pacman_left_narrow, Atlas::pacman_closed, Atlas::pacman_left_narrow };
constexpr std::array<GridPosition,4> right_animation{ Atlas::pacman_right_wide, Atlas::pacman_right_narrow, Atlas::pacman_closed, Atlas::pacman_right_narrow };
constexpr std::array<GridPosition,4> up_animation{ Atlas::pacman_up_wide, Atlas::pacman_up_narrow, Atlas::pacman_closed, Atlas::pacman_up_narrow };

GridPosition PacManAnimation::animationFrame(Direction direction) const {
  switch (direction) {
    case Direction::LEFT:
      return left_animation[animation_position];
    case Direction::RIGHT:
      return right_animation[animation_position];
    case Direction::UP:
      return up_animation[animation_position];
    case Direction::DOWN:
      return down_animation[animation_position];
    case Direction::NONE:
    default:
      return Atlas::pacman_closed;
  }
}

GridPosition PacManAnimation::deathAnimationFrame() const {
  return GridPosition{ animation_position, 1 };
}

void PacManAnimation::updateAnimationPosition(std::chrono::milliseconds time_delta, bool dead) {
  if (dead && animation_position >= 11)
    return;

  animation_position_delta += (0.02) * double(time_delta.count());
  animation_position += size_t(animation_position_delta);

  if (!dead)
      animation_position = animation_position % 4;

  if(animation_position_delta > 1)
      animation_position_delta = animation_position_delta - 1;
}

void PacManAnimation::pause() {
  // when hitting a wall, Pacman's mouth stays wide open
  animation_position = 0;
  animation_position_delta = 0;
}

} // namespace pacman
