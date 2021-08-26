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
   "engine/objects/shapes/area.cpp"
   "engine/objects/shapes/area.hpp"
   "engine/objects/shapes/cuboid.cpp"
   "engine/objects/shapes/cuboid.hpp"
   "engine/objects/shapes/line.cpp"
   "engine/objects/shapes/line.hpp"
   "engine/objects/shapes/polyline.cpp"
   "engine/objects/shapes/polyline.hpp"
   "engine/objects/shapes/rectangle.cpp"
   "engine/objects/shapes/rectangle.hpp"
   "engine/objects/camera.cpp"
   "engine/objects/camera.hpp"
   "engine/objects/geometry.cpp"
   "engine/objects/geometry.hpp"
   "engine/objects/object.cpp"
   "engine/objects/object.hpp"
   "engine/objects/shape.cpp"
   "engine/objects/shape.hpp"
   "engine/objects/texture.cpp"
   "engine/objects/texture.hpp"
   "engine/objects/transform.cpp"
   "engine/objects/transform.hpp"
   "engine/buffer.cpp"
   "engine/buffer.h"
   "engine/engine.cpp" 
   "engine/engine.h"
   "engine/sdl2.h"
   "game.cpp"
   "game.h"
   "main.cpp"
)