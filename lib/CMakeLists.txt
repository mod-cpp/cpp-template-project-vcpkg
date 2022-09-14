find_package(fmt REQUIRED)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp" "*.hpp")
add_library(libhello ${sources})

target_include_directories(libhello PUBLIC include)
target_link_libraries(libhello PUBLIC fmt::fmt)
