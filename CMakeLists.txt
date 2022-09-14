cmake_minimum_required(VERSION 3.16)

include(cmake/vcpkg.cmake)

project(pacman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(scaling-lib)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
