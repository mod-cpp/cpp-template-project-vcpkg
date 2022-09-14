#pragma once
#include <random>

namespace pacman {
[[maybe_unused]] inline std::size_t randomInt(std::size_t min, std::size_t max) {
  // construct a random device
  thread_local std::random_device device;
  // construct a mersenne twister pseudo generator engine, seeded with the device
  thread_local std::mt19937 generator(device());
  // create a distribution
  std::uniform_int_distribution<std::size_t> distribution(min, max);
  return distribution(generator);
}

} // namespace pacman
