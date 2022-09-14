[< Back](README.md)

# 16. Classes and Structs

* [Exercise X2](#exercise-X2)

## Exercise X2

### Refactor out GhostState from GameState

In this exercise we will create a class that abstracts away common functionality.

#### Background: Visibility

The main difference between `class` and `struct` is the default visibility. All
members of a struct are publicly accessible by default. A class on the other hand is
private by default, so some sort of `public:` access is needed to give users access to
things like constructors and functions.

Everything can be made private in a C++ class, even constructors.

#### Background: Default behavior

If possible, we want to rely on the default behavior of the member variables of a
class. This simplifies the design of your class and reduces the things you need to
worry about.

```cpp
struct Position {
  double x = 0;
  double y = 0;
};

struct GridPosition {
  size_t x;
  size_t y;
  GridPosition(size_t x, size_t y)
    : x(x), y(y)
  {}
};
```

When someone creates an instance of `Position` the x and y variables are always set to
0 and there is no other way to create the class.

When someone wants to create an instance of `GridPosition`, they need to give the
constructor the x and y values. You could set them to 0, but they still need to be
given. Trying to create an instance of `GridPosition` with no values given will not
compile.

#### Background: Game State

`GameState` is a class that holds the instances of all the game objects (ghosts,
pacman, pellets, etc). Roughly every 16 milliseconds the `step()` function inside
of `GameState` will be called.

`GameState` will call each member's `update()` function with the current delta time,
this allows each object to know that it should update and how much time has passed
since last it updated. The class also does some checks like if any pellets have been
eaten and if any of the member objects are colliding.

#### Exercise

The ghost functions within `GameState` are usually grouped together. So lets abstract
the ghost updating code into its own class.

1. Create files called `GhostState.hpp` and `GhostState.cpp` and run CMake so they are
   visible within the project.

2. Create a class called `GhostState` within the `.hpp` file.

3. Move all of the ghosts from the `GameState` class into the `GhostState` class. Then
   create a member variable within `GameState` that is of type `GhostState`. You do
   not need to move the `checkColision` function.

4. Move all of the ghost functionality from `GameState` into the `GhostState` class.
   Create functions for this behavior and call those functions from their respective
   locations within `GameState` (update, reset, frighten). You will also need to
   update the `Canvas` class.

5. Compile and run the game, check if everything is working correctly.
