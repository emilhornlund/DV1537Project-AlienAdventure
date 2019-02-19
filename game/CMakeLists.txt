set(EXECUTABLE_NAME "AlienAdventure")

# Globaly find source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Game/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/Game/*.hpp)

add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS} include/Game/classes/GameOverMenuObject.hpp include/Game/classes/LevelCompleteMenuObject.hpp include/Game/classes/PauseMenuObject.hpp)
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${EXECUTABLE_NAME} LINK_PUBLIC CoreGameLib)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${PROJECT_BINARY_DIR}/resources)