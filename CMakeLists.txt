cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME "AlienAdventure")
project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE release)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.cpp" "src/*.mm")

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(SFML 2 COMPONENTS audio graphics window system network)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR} "${PROJECT_SOURCE_DIR}/include")
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources/ DESTINATION ${PROJECT_BINARY_DIR}/resources)
