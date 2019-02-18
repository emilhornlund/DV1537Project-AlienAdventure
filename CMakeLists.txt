cmake_minimum_required(VERSION 3.12)
set(EXECUTABLE_NAME "AlienAdventure")
project(${EXECUTABLE_NAME})

SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

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

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)

add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})

find_package(SFML 2 COMPONENTS audio graphics window system network)
find_package(TinyXML2)

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include ${SFML_INCLUDE_DIR} ${TINYXML2_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} LINK_PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${TINYXML2_LIBRARIES})

install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources/ DESTINATION ${PROJECT_BINARY_DIR}/resources)