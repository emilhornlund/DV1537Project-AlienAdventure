cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME "AlienAdventure")
project(${PROJECT_NAME})

SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_CXX_STANDARD 11)

file(GLOB INC
        "${PROJECT_SOURCE_DIR}/include/core/classes/*.hpp"
        "${PROJECT_SOURCE_DIR}/include/game/classes/*.hpp"
        "${PROJECT_SOURCE_DIR}/include/core/interfaces/*.hpp"
        "${PROJECT_SOURCE_DIR}/include/game/interfaces/*.hpp"
)

file(GLOB SRC
        "${PROJECT_SOURCE_DIR}/src/core/classes/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/game/classes/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/core/interfaces/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/game/interfaces/*.cpp"
)

add_executable(${PROJECT_NAME} ${INC} "${PROJECT_SOURCE_DIR}/src/main.cpp" ${SRC})

find_package(SFML 2 COMPONENTS audio graphics window system network)

if (SFML_FOUND)
    include_directories(
            "${SFML_INCLUDE_DIR}"
            "${PROJECT_SOURCE_DIR}/include"
    )
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources/ DESTINATION ${PROJECT_BINARY_DIR}/resources)