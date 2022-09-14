#pragma once

#include "Ghost.hpp"

namespace pacman {

class Pinky final : public Ghost {
public:
  Pinky();
  void setTarget(GridPosition pacManPos, Direction pacManDir);

protected:
  double speed() const override;
  Position initialPosition() const override;

private:
  Position scatterTarget() const;
  static constexpr Position initial_position = { 11.5, 14 };
  static constexpr Position scatter_target = { 3, -2 };
};

} // namespace pacman
