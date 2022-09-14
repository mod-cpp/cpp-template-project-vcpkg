find_package(SFML COMPONENTS COMPONENTS window graphics CONFIG REQUIRED)

add_library(scaling-lib ${sources})

target_include_directories(scaling-lib PUBLIC .)
target_link_libraries(scaling-lib PUBLIC sfml-graphics)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    target_sources(scaling-lib PRIVATE Scaling.mm)
else()
    target_sources(scaling-lib PRIVATE Scaling.cpp)
endif ()
