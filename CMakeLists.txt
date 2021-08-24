cmake_minimum_required(VERSION 3.20)

message(STATUS "Using CMake ${CMAKE_VERSION}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# set up project
project(BoardGame)
message(STATUS ${PROJECT_NAME})

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Release)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${CMAKE_SOURCE_DIR}/source)

set(ALLOW_UNITY_BUILD OFF)
cmake_dependent_option(CMAKE_UNITY_BUILD "Use Unity Build" ON "ALLOW_UNITY_BUILD" OFF)
message(STATUS "Unity builds are ${CMAKE_UNITY_BUILD}")

SET(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
SET(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
SET(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support

# Prepare the build
# add_subdirectory(source/common)
# add_subdirectory(source/DontWorry)
add_subdirectory(source/FastFloor)
#add_subdirectory(source/LudoBoard)
#add_subdirectory(source/WallPaint)
