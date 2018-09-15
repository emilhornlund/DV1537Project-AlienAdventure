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
        "${CMAKE_CURRENT_SOURCE_DIR}/AlienAdventure.h.in"
        "${PROJECT_BINARY_DIR}/AlienAdventure.h"
)
include_directories("${PROJECT_BINARY_DIR}")

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

if (APPLE)
    add_executable(${EXECUTABLE_NAME} MACOSX_BUNDLE ${INC} "${PROJECT_SOURCE_DIR}/src/main.cpp" ${SRC})
else()
    add_executable(${EXECUTABLE_NAME} ${INC} "${PROJECT_SOURCE_DIR}/src/main.cpp" ${SRC})
endif()

find_package(SFML 2 COMPONENTS audio graphics window system network)
if (SFML_FOUND)
    include_directories(
            "${SFML_INCLUDE_DIR}"
            "${PROJECT_SOURCE_DIR}/include"
    )
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

if(APPLE)
    #SET(CMAKE_OSX_SYSROOT ${IPHONE_TOOLCHAIN_DIR}/sys)
    MACRO(ADD_FRAMEWORK fwname appname)
        FIND_LIBRARY(FRAMEWORK_${fwname}
                NAMES ${fwname}
                PATHS ${CMAKE_OSX_SYSROOT}/System/Library
                PATH_SUFFIXES Frameworks
                NO_DEFAULT_PATH)
        IF( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
            MESSAGE(ERROR ": Framework ${fwname} not found")
        ELSE()
            TARGET_LINK_LIBRARIES(${appname} ${FRAMEWORK_${fwname}})
            MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
        ENDIF()
    ENDMACRO(ADD_FRAMEWORK)
    ADD_FRAMEWORK(CoreFoundation ${EXECUTABLE_NAME})

    set(MAKE_INSTALL_NAME_DIR @rpath)

    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in
            OUTPUT_NAME ${EXECUTABLE_NAME}
    )

    file(GLOB BUNDLE_RESOURCE_FILES
            "${PROJECT_SOURCE_DIR}/resources/*"
    )
    set_source_files_properties(${BUNDLE_RESOURCE_FILES} PROPERTIES
            MACOSX_PACKAGE_LOCATION Resources
    )

    ADD_CUSTOM_COMMAND(TARGET ${EXECUTABLE_NAME} POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/tools/macOS/third_party_libs_tool "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/../..")

    set(BUNDLE_PATH ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_NAME}.app)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${BUNDLE_PATH}/Contents/Resources)
else()
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources/ DESTINATION ${PROJECT_BINARY_DIR}/resources)
endif()
