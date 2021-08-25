cmake_minimum_required(VERSION 3.20)

project(FastFloor CXX)
message(STATUS ${PROJECT_NAME})

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# glm + imgui + spdlog

find_package(SDL2 CONFIG REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})

#find_package(SDL2PP REQUIRED)
#include_directories(${SDL2PP_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} WIN32)
#target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2PP_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} 
   fmt::fmt SDL2::SDL2 SDL2::SDL2main 
#   SDL2::SDL2_image SDL2::SDL2_mixer SDL2::SDL2_ttf
#   ${SDL2PP_LIBRARIES}
)

target_sources(${PROJECT_NAME} PRIVATE
   "engine.cpp" 
   "engine.h"
   "game.cpp"
   "game.h"
   "main.cpp"
   "sdl2.h"
)