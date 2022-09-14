[< Back](README.md)

# 16. Classes and Structs

* [Exercise 160](#exercise-160)
* [Exercise 161](#exercise-161)

## Exercise 160

### Simple class

1. Create an empty class named `Clyde` within the `.hpp` file.
2. Look at other ghost `.hpp` files and see how they define the class. It does not
   need to inherit from the `Ghost` base class and it does not need any functions.

<details>
   <summary>Solution</summary>

Clyde.hpp

```cpp
#pragma once

#include "Ghost.hpp"

namespace pacman {

class Clyde {

};

} // namespace pacman

```

Clyde.cpp

```cpp
#include "Clyde.hpp"

namespace pacman {

} // namespace pacman
```

</details>

## Exercise 161

### Add Clyde as a Ghost

#### Background: Clyde

We have three ghosts within the project. [Blinky](../../lib/include/Blinky.hpp)
, [Inky](../../lib/include/Inky.hpp)
and [Pinky](../../lib/include/Pinky.hpp). But [Clyde](../../lib/include/Clyde.hpp) is
missing. Implement Clyde and their behavior.

Clyde chases PacMan, so you need to know where PacMan is currently located. But Clyde
gets scared and runs back to its scatter target when PacMan gets too close (less than
8 the size of a cell). Clyde also has the scatter and eyes behaviors as the other
ghosts.

#### Exercise

1. Clyde should inherit from Ghost
2. Make simple implementations of the functions to make it compile
3. Clyde should start at Position { .x = 15.5, .y = 14 }
4. Modify [Canvas.cpp](../../lib/Canvas.cpp) to make sure Clyde is rendered.
   Otherwise, it will not appear on screen.
5. Clyde's scatter target is { .x = 0, .y = 30 }
6. Clyde always targets its scatter target, unless PacMan is further than 8 tiles away
7. Update [GameState.cpp](../../lib/GameState.cpp) with calls to the functions in
   Clyde to make Clyde move.

<details>
   <summary>Hint Canvas.cpp and GameState.hpp</summary>

Add a line to `Canvas::render` to make sure that Clyde is rendered. This requires a
change to [GameState.hpp](../../lib/include/GameState.hpp) also.

</details>

<details>
   <summary>Solution: Canvas.cpp</summary>

[Canvas.cpp](../../lib/Canvas.cpp)

```cpp
  // Call renderGhost with clyde
  renderGhost(gameState.clyde);
```

</details>

<details>
   <summary>Solution: GameState.hpp</summary>

[GameState.hpp](../../lib/include/GameState.hpp)

```cpp
  // Create a Clyde object in GameState together with the other ghosts
  Clyde clyde;
```

</details>

<details>
   <summary>Solution: Clyde.hpp</summary>

[Clyde.hpp](../../lib/include/Clyde.hpp)

```cpp
#pragma once

#include "Ghost.hpp"

namespace pacman {

class Clyde final : public Ghost {
public:
  Clyde();
  void setTarget(Position pacManPos);

protected:
  double speed() const override;
  Position initialPosition() const override;

private:
  Position scatterTarget() const;
  static constexpr Position initial_position = { 15.5, 14 };
  static constexpr Position scatter_target = { 0, 30 };
};

} // namespace pacman
```

</details>

<details>
   <summary>Solution: Clyde.cpp</summary>

[Clyde.cpp](../../lib/Clyde.cpp)

```cpp
#include "Clyde.hpp"

namespace pacman {

Clyde::Clyde()
  : Ghost(Atlas::Ghost::clyde, initial_position) {}

double Clyde::speed() const {
  if (state == State::Eyes)
    return 2;
  if (state == State::Frightened)
    return 0.5;
  return 0.75;
}

void Clyde::setTarget(Position pacManPos) {
  if (state == State::Eyes) {
    target = initialPosition();
    return;
  }

  if (isInPen()) {
    target = penDoorPosition();
    return;
  }

  // Clyde always target its scatter target, unless pacman is further than 8 tiles away
  target = scatterTarget();
  if (state == State::Scatter) {
    return;
  }

  const auto distanceFomPacMan = std::hypot(pos.x - pacManPos.x, pos.y - pacManPos.y);
  if (distanceFomPacMan > 8) {
    target = pacManPos;
  }
}

Position Clyde::initialPosition() const {
  return initial_position;
}

Position Clyde::scatterTarget() const {
  return scatter_target;
}

} // namespace pacman
```

</details>

<details>
   <summary>Hint GameState.cpp</summary>

Search for the other ghosts in the file and add similar calls for Clyde.

</details>

<details>
   <summary>Solution: GameState.cpp</summary>

[GameState.cpp](../../lib/GameState.cpp)

```cpp
  // In GameState::step
  clyde.setTarget(pacMan.position());
  clyde.update(delta);

  // In GameState::step
  checkCollision(clyde);

  // In GameState::handleDeathAnimation
  clyde.reset();

  // In GameState::eatPellets
  clyde.frighten();
```

</details>
