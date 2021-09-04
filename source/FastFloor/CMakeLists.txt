cmake_minimum_required(VERSION 3.20)

project(FastFloor CXX)
message(STATUS ${PROJECT_NAME})

find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# glm + imgui + spdlog
find_package(GLEW CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} WIN32) # WIN32

target_link_libraries(${PROJECT_NAME} 
   fmt::fmt SDL2::SDL2 SDL2::SDL2main glm::glm GLEW::GLEW 
)

#configure_file("shader/Camera.fs" "shader/Camera.fs" COPYONLY)

target_sources(${PROJECT_NAME} PRIVATE
   "images/awesomeface.png"
   "images/container.jpg"
   "images/grumpy-cat.bmp"
   "images/grumpy-cat.png"
   "images/test.png"
   "images/wall.jpg"

   "shader/Camera.fs"
   "shader/Camera.vs"
   "shader/Complex.fs"
   "shader/Complex.vs"
   "shader/Coords.fs"
   "shader/Coords.vs"
   "shader/Simple.fs"
   "shader/Simple.vs"
   "shader/Texture.fs"
   "shader/Texture.vs"
   "shader/Transform.fs"
   "shader/Transform.vs"

   "source/objects/camera.cpp"
   "source/objects/camera.hpp"

   "source/shapes/base/common.hpp"
   "source/shapes/base/shader.cpp"
   "source/shapes/base/shader.hpp"
   "source/shapes/base/texture.cpp"
   "source/shapes/base/texture.hpp"
   "source/shapes/base/transform.cpp"
   "source/shapes/base/transform.hpp"

#   "source/shapes/area.cpp"
#   "source/shapes/area.hpp"
#   "source/shapes/cuboid.cpp"
#   "source/shapes/cuboid.hpp"
#   "source/shapes/line.cpp"
#   "source/shapes/line.hpp"
#   "source/shapes/polyline.cpp"
#   "source/shapes/polyline.hpp"
   "source/shapes/rectangle.cpp"
   "source/shapes/rectangle.hpp"
   "source/shapes/shape.hpp"
   "source/shapes/shape.cpp"

   "source/engine.cpp" 
   "source/engine.h"
   "source/sdl2.h"

   "game.cpp"
   "game.h"
   "main.cpp"
)