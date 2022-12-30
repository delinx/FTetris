cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME ftetris)

# Adding Raylib
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)

project(
  ${PROJECT_NAME}
  VERSION 0.0.1
  LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp src/gameLoop.cpp src/types/grid.cpp src/types/block.cpp src/types/shape.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(UNIT_TEST)
  add_definitions(-DUNIT_TEST)
endif()
