find_package(SFML COMPONENTS COMPONENTS window graphics system CONFIG REQUIRED)
find_package(fmt REQUIRED)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_package(OpenGL REQUIRED COMPONENTS OpenGL GLX)
endif ()

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_library(libpacman ${sources})

target_include_directories(libpacman PUBLIC include)
target_link_libraries(libpacman PUBLIC scaling-lib fmt::fmt sfml-graphics)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(libpacman PUBLIC OpenGL::OpenGL OpenGL::GLX)
endif ()