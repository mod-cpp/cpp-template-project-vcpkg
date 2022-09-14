[< Back](README.md)

# 22. std::vector

* [Exercise 220](#exercise-220)
* [Exercise 221](#exercise-221)
* [Exercise 222](#exercise-222)

## Exercise 220

### Use reserve in `initialPelletPositions` in [Board.cpp](../../lib/Board.cpp)

To avoid having to resize the vector too many times, we can preemptively reserve space
for elements. At a glance, we can estimate that there are pellets on a third of the
grid. This is not accurate, so we might either reserve too much or too little memory,
but this will still be faster than not calling reserve at all. This will be very
noticeable on both very large vectors (tens of thousands of elements), Or small
vectors in functions called very frequently.

```cpp
std::vector<GridPosition> initialPelletPositions() {
  std::vector<GridPosition> positions;

  for (std::size_t row = 0; row < ROWS; row++) {
    for (std::size_t column = 0; column < COLUMNS; column++) {
      if (board[row][column] == int(Cell::pellet))
        positions.emplace_back(column, row);
    }
  }
  return positions;
}

```

<details>
   <summary>Solution</summary>

```cpp
std::vector<GridPosition> initialPelletPositions() {
  std::vector<GridPosition> positions;

  positions.reserve((ROWS * COLUMNS) / 3);

  for (std::size_t row = 0; row < ROWS; row++) {
    for (std::size_t column = 0; column < COLUMNS; column++) {
      if (board[row][column] == int(Cell::pellet))
        positions.emplace_back(column, row);
    }
  }
  return positions;
}

```

</details>

## Exercise 221

### Implement `PacManAI::pelletClosestToPacman`

Implement [PacManAI::pelletClosestToPacman][1] and test your implementation with the
test in [testPacmanAI.cpp][2] called _"Find pellet closest to PacMan"_

Note: In the [testPacmanAI.cpp][2] test called _"Find pellet closest to PacMan"_ a
Catch2 feature is used called a Data Generator. This lets you reuse the test across
different input values, see the [Catch2 documentation for Data Generators][3].

The function should return the position of the pellet that is "closest" to PacMan.

```cpp
GridPosition PacManAI::pelletClosestToPacman(GridPosition pacmanGridPosition,
                                             std::vector<GridPosition> & pellets) {
  return {0, 0};
}
```

<details>
   <summary>Hint 1</summary>

Use the `positionDistance` function to find the distance to PacMan.

</details>

<details>
   <summary>Solution</summary>

```cpp
GridPosition PacManAI::pelletClosestToPacman(GridPosition pacmanGridPosition,
                                             std::vector<GridPosition> & pellets) {
  GridPosition closestPellet = { 0, 0 };
  double closestDistance = std::numeric_limits<double>::infinity();

  for (const auto & pellet : pellets) {
    const double distance = positionDistance(pacmanGridPosition, pellet);
    if (distance < closestDistance) {
      closestDistance = distance;
      closestPellet = pellet;
    }
  }

  return closestPellet;
}
```

</details>

## Exercise 222

### Try out your AI

* Press 'a' on the keyboard

[1]: ../../lib/PacManAI.cpp
[2]: ../../test/unit_tests/testPacmanAI.cpp
[3]: https://github.com/catchorg/Catch2/blob/v2.x/docs/generators.md
