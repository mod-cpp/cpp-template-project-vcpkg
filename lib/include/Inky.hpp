#pragma once

#include "Ghost.hpp"

namespace pacman {

class Inky final : public Ghost {
public:
  Inky();
  void setTarget(GridPosition pacManPos, Direction pacManDir, GridPosition blinkyPos);

protected:
  double speed() const override;
  Position initialPosition() const override;

private:
  Position scatterTarget() const;
  static constexpr Position initial_position = { 13.5, 14 };
  static constexpr Position scatter_target = { 27, 30 };
};

} // namespace pacman
