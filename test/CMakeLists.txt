find_package(Catch2 REQUIRED)

file(GLOB unit_tests_sources CONFIGURE_DEPENDS "unit_tests/*.cpp")
add_executable(pacman_unit_tests ${unit_tests_sources})
target_link_libraries(pacman_unit_tests Catch2::Catch2 libpacman)
target_compile_definitions(pacman_unit_tests PUBLIC CATCH_CONFIG_CONSOLE_WIDTH=300)

file(GLOB exercises_sources CONFIGURE_DEPENDS "exercises/*.cpp")
add_executable(pacman_exercises ${exercises_sources})
target_link_libraries(pacman_exercises Catch2::Catch2 libpacman)
target_compile_definitions(pacman_exercises PUBLIC CATCH_CONFIG_CONSOLE_WIDTH=300)

include(Catch)
catch_discover_tests(pacman_unit_tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/)
catch_discover_tests(pacman_exercises WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/)
