find_package(Catch2 REQUIRED)

file(GLOB unit_tests_sources CONFIGURE_DEPENDS "*.cpp")
add_executable(unit_tests ${unit_tests_sources})
target_link_libraries(unit_tests Catch2::Catch2 libhello)

include(Catch)
catch_discover_tests(unit_tests)
