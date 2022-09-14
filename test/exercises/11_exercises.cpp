#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

// 11. Introduction
namespace exercises_11 {

TEST_CASE("Exercise 11x : Make sure running exercise tests work", "[11]") {
  REQUIRE(true == true);
}

// HINT: To enable a test remove [.] from the tags on the test
TEST_CASE("Exercise 111 : Enable the test and make it green", "[.][11]") {
  REQUIRE(true == false);
}

// HINT: https://github.com/catchorg/Catch2/blob/v2.x/docs/assertions.md
TEST_CASE("Exercise 112 : Make both asserts run (distinguish between REQUIRE and CHECK in Catch2)", "[.][11]") {
  REQUIRE(true == false);
  CHECK(false == true);
}

} // namespace exercises_11
