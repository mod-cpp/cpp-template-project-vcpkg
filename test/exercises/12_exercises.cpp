#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test
#include <string>

// 12. Hello World
namespace exercises_12 {

// HINT: To enable a test remove [.] from the tags on the test
TEST_CASE("Exercise 122 : String concatenation", "[.][12]") {
  std::string hello = "SOMETHING";
  std::string world = " HERE";
  REQUIRE(hello + world == "Hello World");
}

// HINT: To enable a test remove [.] from the tags on the test
TEST_CASE("Exercise 123 : std::string append", "[.][12]") {
  std::string hello_world = "Hello ";
  // append "World"
  REQUIRE(hello_world == "Hello World");
}

// HINT: To enable a test remove [.] from the tags on the test
TEST_CASE("Exercise 124 : Function call", "[.][12]") {
  std::string hello_world = "CALL A FUNCTION";
  REQUIRE(hello_world == "Hello World");
}

} // namespace exercises_12
