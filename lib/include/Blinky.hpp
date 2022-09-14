#pragma once

#include "Ghost.hpp"

namespace pacman {

class Blinky final : public Ghost {
public:
  Blinky();
  void setTarget(Position pacManPos);

protected:
  double speed() const override;
  Position initialPosition() const override;

private:
  Position scatterTarget() const;
  static constexpr Position initial_position = { 13.5, 11 };
  static constexpr Position scatter_target = { 25, -3 };
};

} // namespace pacman
