[< Back](README.md)

# 13. Game

* [Exercise 130](#exercise-130)

## Exercise 130

### Navigating the code

#### Background: Pac-Man project

The project is split into three parts (solutions).

- [**libpacman**](../../lib/CMakeLists.txt) - This is where the entire game lives
- [**pacman**](../../src/CMakeLists.txt) - This is the project that generates the
  executable, the only thing [main](../../src/main.cpp) does is to create the game
  instance and call the `run()` function
- [**pacman_unit_tests**](../CMakeLists.txt) - All the unit tests for the game

##### libpacman

The libpacman solution has 3 main parts.

- [**Game**](../../lib/include/Game.hpp) - A class that holds the Canvas and GameState
  objects
- [**Canvas**](../../lib/include/Canvas.hpp) - A class that uses the SFML library to
  draw objects to the screen. Also manages the game window
- [**GameState**](../../lib/include/GameState.hpp) - A class that holds all of the
  state for Pac-Man. Contains classes like the
  Ghosts ([Blinky](../../lib/include/Blinky.hpp), [Inky](../../lib/include/Inky.hpp)
  and [Pinky](../../lib/include/Pinky.hpp)), [PacMan](../../lib/include/PacMan.hpp)
  and the [Pellets](../../lib/include/Pellets.hpp) PacMan eats.

##### Updating the game state

Within the [Game.cpp](../../lib/Game.cpp) file there is a function called `run()`,
this function draws the current game state to screen `canvas.update(gameState);` but
it only calls the game state update function at a fixed interval, it also sends this
interval to the game state update function `gameState.step(delta_time);`

Then in the `step()` function in [GameState.cpp](../../lib/GameState.cpp)
the magic happens. Each object in the game world is updated and the state of the game
world is checked. Did Pac-Man just eat a pellet? Are the ghosts touching Pac-Man?
Which direction is Pac-Man moving?

##### The game board

The game board is stored as a two-dimensional array of integers in
the [Board.cpp](../../lib/Board.cpp) file. The array itself is only accessible
within that file, which is why we export helper functions that use the array as a
global variable. This exporting happens in `Board.hpp`

##### Ghosts

All ghosts inherit from the parent Ghost class defined
in [Ghost.hpp](../../lib/include/Ghost.hpp) and [Ghost.cpp](../../lib/Ghost.cpp),
there are a couple of pure virtual functions those ghosts need to implement, otherwise
you are not able to create an instance of them. A ghost stores its current location,
its current target and other state regarding if it is frightened or not. At
each `update()` call a ghost needs to decide what its target is and which direction it
should turn next.

##### Pac-Man

[PacMan](../../lib/include/PacMan.hpp) has similar state to a Ghost, like direction
and position. Pac-Man's behavior is also similar in `update()` as we need to determine
where to place Pac-Man in the next game state. But the information on which direction
to turn comes from the player (or a bot).

##### Unit tests

Because updates of game state and drawing the game on screen are completely separate,
we can create game state within unit tests and give it arbitrary delta time and call
whatever functions we want to simulate the game being played. Most unit tests only
focus on one single class but some (like
[testFruits.cpp](../unit_tests/testFruits.cpp)) use the
[GameState](../../lib/include/GameState.hpp) class.

### Exercise

1. Familiarize yourself with the codebase by trying to find the files that contain the
   code mentioned in the slides
2. In which file is the logic for the ghost behavior implemented?
3. What information is tracked as part of the score?

<details>
   <summary>Solution</summary>

2. The behavior of the ghosts is mostly implemented in Ghost.cpp, but each of the
   ghosts has its own file that implements its personality.

3. The score keeps track of the number of lives, pellets and fruits, as well as the
   number of points earned by the player.

</details>
