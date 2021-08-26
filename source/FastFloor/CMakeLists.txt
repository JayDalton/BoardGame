cmake_minimum_required(VERSION 3.20)

project(FastFloor CXX)
message(STATUS ${PROJECT_NAME})

find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# glm + imgui + spdlog
find_package(GLEW CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} WIN32)

target_link_libraries(${PROJECT_NAME} 
   fmt::fmt SDL2::SDL2 SDL2::SDL2main GLEW::GLEW
)

target_sources(${PROJECT_NAME} PRIVATE
   "buffer.cpp"
   "buffer.h"
   "engine.cpp" 
   "engine.h"
   "game.cpp"
   "game.h"
   "main.cpp"
   "sdl2.h"
)