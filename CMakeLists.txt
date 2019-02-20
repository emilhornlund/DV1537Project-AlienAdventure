cmake_minimum_required(VERSION 3.12)
project("DV1537Project")

SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_CXX_STANDARD 11)

include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory(dependencies/SFML)
add_subdirectory(dependencies/tinyxml2)
add_subdirectory(lib)
add_subdirectory(game)
