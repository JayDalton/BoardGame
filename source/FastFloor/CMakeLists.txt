cmake_minimum_required(VERSION 3.20)

project(FastFloor CXX)
message(STATUS ${PROJECT_NAME})

# glm + spdlog + imgui ?
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

find_package(GLEW CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

find_package(freetype CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Assimp CONFIG REQUIRED)

add_executable(${PROJECT_NAME}) # WIN32

add_custom_command(
   TARGET FastFloor POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_SOURCE_DIR}/source/FastFloor/images/ 
      $<TARGET_FILE_DIR:FastFloor>/images)

add_custom_command(
   TARGET FastFloor POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_SOURCE_DIR}/source/FastFloor/shader/ 
      $<TARGET_FILE_DIR:FastFloor>/shader)

#add_custom_command(
#   TARGET FastFloor POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy
#      ${CMAKE_SOURCE_DIR}/test/input.txt
#      ${CMAKE_CURRENT_BINARY_DIR}/input.txt)

target_link_libraries(${PROJECT_NAME} 
   SDL2::SDL2 SDL2::SDL2main 
   glm::glm GLEW::GLEW 
   imgui::imgui
   freetype
)

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
   "shader/Colored.fs"
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

   "source/overlay/imgui_impl_opengl2.cpp"
   "source/overlay/imgui_impl_opengl2.h"
   "source/overlay/imgui_impl_opengl3.cpp"
   "source/overlay/imgui_impl_opengl3.h"
   "source/overlay/imgui_impl_opengl3_loader.h"
   "source/overlay/imgui_impl_sdl.cpp"
   "source/overlay/imgui_impl_sdl.h"
   "source/overlay/imgui_impl_sdlrenderer.cpp"
   "source/overlay/imgui_impl_sdlrenderer.h"
   "source/overlay/imgui_impl_win32.cpp"
   "source/overlay/imgui_impl_win32.h"

   "source/shapes/base/buffer.cpp"
   "source/shapes/base/buffer.hpp"
   "source/shapes/base/common.hpp"
   "source/shapes/base/mesh.cpp"
   "source/shapes/base/mesh.hpp"
   "source/shapes/base/model.cpp"
   "source/shapes/base/model.hpp"
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
#   "source/shapes/rectangle.cpp"
#   "source/shapes/rectangle.hpp"
   "source/shapes/shape.hpp"
   "source/shapes/shape.cpp"

   "source/engine.cpp" 
   "source/engine.h"
   "source/sdl2.h"

   "game.cpp"
   "game.h"
   "main.cpp"
   "model.cpp"
   "model.h"
)