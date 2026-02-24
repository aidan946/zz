cmake_minimum_required(VERSION 4.23)
project(zz VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create executable
add_executable(zz
    src/main.cpp
    src/parsing.cpp
    src/printer.cpp
    src/sorter.cpp
)

# Compiler flags scoped to this target
target_compile_options(zz PRIVATE
    -Wall -Wextra -Wpedantic
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
    $<$<CONFIG:Debug>:-g -O0>
)

# Set output directories
set_target_properties(zz PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Installation
install(TARGETS zz
    RUNTIME DESTINATION bin
)
