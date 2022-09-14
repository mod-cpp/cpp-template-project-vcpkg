[< Back](../README.md)

# Exercise: Increased Ghost Speed

## Background:

Currently the ghosts move at a fixed rate. But in the original game, the ghosts would
move slightly faster and faster as the game went on.

Implement a way to incrementally increase the ghost speed over time. The speed
function takes in the current game state so that can be used. The speed should not
slowly increase for each update, so something like adding onto the speed value over
time is not correct behavior.

You could increase the speed after each time the ghost is eaten for example, or
increment the speed by a certain amount after N seconds.

Also ask yourself, how would you test this?
