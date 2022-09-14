// Your includes here.
#include "catch2/catch.hpp"

// Simple test examples.

TEST_CASE("Hello", "[hello]") {
  REQUIRE(1 + 1 == 2);
  REQUIRE_FALSE(1 + 1 == 1);
}
