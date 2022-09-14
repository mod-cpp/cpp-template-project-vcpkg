add_executable(hello main.cpp)
target_link_libraries(hello PUBLIC libhello)

set_target_properties(hello
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
