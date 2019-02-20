cmake_minimum_required(VERSION 3.12)
project("DV1537Project")

SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory(dependencies/SFML)
add_subdirectory(dependencies/tinyxml2)
add_subdirectory(lib)
add_subdirectory(game)
