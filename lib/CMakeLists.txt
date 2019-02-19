set(LIBRARY_NAME "CoreGameLib")

set(LIB_VERSION_MAJOR 0)
set(LIB_VERSION_MINOR 1)
set(LIB_VERSION_PATCH 0)
set(LIB_VERSION "${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH}")

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME}.h.in"
        "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}.h"
)

# Globaly find source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/Core/*.hpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS audio graphics window system network)
find_package(TinyXML2)

add_library(${LIBRARY_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${LIBRARY_NAME} LINK_PUBLIC ${SFML_LIBRARIES} ${TINYXML2_LIBRARIES})

target_include_directories(${LIBRARY_NAME} PUBLIC include ${SFML_INCLUDE_DIR} ${TINYXML2_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
