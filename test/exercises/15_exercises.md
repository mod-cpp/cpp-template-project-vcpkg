[< Back](README.md)

# 15. Compilation, Linking and Assets

* [Exercise 150](#exercise-150)
* [Exercise 151](#exercise-151)

## Exercise 150

### Add files to the build

In this exercise we will add a couple of files to the project.

#### Background: CMake

As described in the slides, the project is defined by several CMake files. The ones we
are interested is [CMakeLists.txt][1] in the root project folder and
the [CMakeLists.txt][2] file in the `lib` folder.

You can see that the root CMake file is adding the `lib` subdirectory, this means that
it is looking for a `CMakeLists.txt` file within that folder.

The CMake file in the `lib` folder describes a few package requirements and then it
does this

```cmake
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp" "*.hpp")
```

Here it is creating a CMake variable called `sources` that will contain all `.cpp`
and `.hpp` files within the `lib`
folder. This means that if we want to add new files, we don't have to list them here,
as any applicable files are included. But adding a file will not automatically add the
file in the IDE, as CMake needs to be run again for those changes to apply.

### Exercise

One of the Pac-Man ghosts is missing. We will fully implement this ghost later but for
now let's add the `.cpp`
and `.hpp` files to the project.

1. Create a `Clyde.hpp` in the `lib/include` folder and a `Clyde.cpp` file in
   the `lib` folder.

2. Run CMake again and see your IDE update to include these new files. You can try
   compiling again and see what happens.

3. Include the `Clyde.hpp` file within the `Clyde.cpp` file, and add `#pragma once`
   to `Clyde.hpp`.

4. Include `Clyde.hpp` in [GameState.hpp][3] and rebuild

<details>
   <summary>Solution</summary>

[Clyde.hpp](../../lib/include/Clyde.hpp)

```cpp
#pragma once
```

[Clyde.cpp](../../lib/Clyde.cpp)

```cpp
#include "Clyde.hpp"
```

[GameState.hpp](../../lib/include/GameState.hpp)
```cpp
// Include the header in GameState.hpp
#include "Clyde.hpp"
```

</details>

## Exercise 151

### Create and run a unit test

#### Background: Board Unit Tests

The game board is covered by unit tests. They are located in
the [testBoard.cpp](../unit_tests/testBoard.cpp) file within the `test/unit_tests`
directory. They don't check every single tile on the board, but they do assume that
the board shape is not changed significantly. If you change the board layout you might
have to change some unit tests to match.

Unit tests are broken down into test cases, in this file it is focused on a test case
per function. A `TEST_CASE` takes two arguments, a test name and a tag. The test name
needs to be unique and for the tag we use the section of the game we are testing.
Think of them like functions that are called when testing.

#### Exercise

1. Add a new unit test `TEST_CASE` for `isWall`. To test `isWall` we need to add it
   the [Board.hpp](../../lib/include/Board.hpp) file because it should be accessible
   within the [testBoard.cpp](../unit_tests/testBoard.cpp)
   file. Check for a couple of cases, similarly to the
   `isWalkableForPacMan` test. Remember since the unit tests are not inside
   the `pacman` namespace, we need to append
   `pacman::` to the function calls.

2. Compile the project and run the unit tests. They should all be passing and if they
   are not then check which unit test is failing and figure out what was causing the
   issue. If all goes well you can run the game.


<details>
   <summary>Solution</summary>

* Add `isWall` to `Board.hpp`

```cpp
// Add the function declaration to the Board header file inside of namespace pacman
bool isWall(GridPosition point);
```

* Add a test for `isWall` to `testBoard.cpp`

```cpp
TEST_CASE("Is wall", "[board]") {
  REQUIRE(pacman::isWall(pacman::GridPosition{ 0, 0 }));
  REQUIRE(pacman::isWall(pacman::GridPosition{ 1, 0 }));
  REQUIRE(pacman::isWall(pacman::GridPosition{ 0, 1 }));
  REQUIRE_FALSE(pacman::isWall(pacman::GridPosition{ 11, 13 })); // pen
  REQUIRE_FALSE(pacman::isWall(pacman::GridPosition{ 1, 1 })); // pellet
  REQUIRE_FALSE(pacman::isWall(pacman::GridPosition{ 1, 2 })); // pellet
}
```
</details>

[1]: ../../CMakeLists.txt
[2]: ../../lib/CMakeLists.txt
[3]: ../../lib/include/GameState.hpp
