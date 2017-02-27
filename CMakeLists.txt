cmake_minimum_required(VERSION 3.6)
project(Tree_evol)

set(CMAKE_CXX_STANDARD 14)

link_directories(libs)
include_directories(include)

# Dynamic builds

# Debug build
set(SOURCE_FILES main.cpp)
add_executable(tree_evol-d ${SOURCE_FILES})
target_compile_definitions(tree_evol-d PRIVATE)
target_link_libraries(tree_evol-d sfml-graphics-d sfml-window-d sfml-system-d Box2D)

# Release build
set(SOURCE_FILES main.cpp)
add_executable(tree_evol ${SOURCE_FILES})
target_compile_definitions(tree_evol PRIVATE)
target_link_libraries(tree_evol sfml-graphics sfml-window sfml-system Box2D)

# Static builds

# Debug build
set(SOURCE_FILES main.cpp)
add_executable(tree_evol-s-d ${SOURCE_FILES})
target_compile_definitions(tree_evol-s-d PRIVATE SFML_STATIC=1)
target_link_libraries(tree_evol-s-d sfml-graphics-s-d sfml-window-s-d sfml-system-s-d Box2D)

# Release build
set(SOURCE_FILES main.cpp)
add_executable(tree_evol-s ${SOURCE_FILES})
target_compile_definitions(tree_evol-s PRIVATE SFML_STATIC=1)
target_link_libraries(tree_evol-s sfml-graphics-s sfml-window-s sfml-system-s Box2D)