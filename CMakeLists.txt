cmake_minimum_required(VERSION 3.12)
project("DV1537Project")

SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")

# set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

configure_file(
        "${PROJECT_SOURCE_DIR}/AlienAdventure.h.in"
        "${PROJECT_BINARY_DIR}/AlienAdventure.h"
)

include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib)
add_subdirectory(game)
