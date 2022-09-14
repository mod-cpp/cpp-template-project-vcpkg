cmake_minimum_required(VERSION 3.16)

include(cmake/vcpkg.cmake)

project(hello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
