cmake_minimum_required(VERSION 3.20)

project(WasmPaint CXX)
message(STATUS ${PROJECT_NAME})

# glm + spdlog + imgui ?
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

find_package(GLEW CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME}) # WIN32

#add_custom_command(
#   TARGET FastFloor POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#      ${CMAKE_SOURCE_DIR}/source/FastFloor/images/ 
#      $<TARGET_FILE_DIR:FastFloor>/images)

#add_custom_command(
#   TARGET FastFloor POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#      ${CMAKE_SOURCE_DIR}/source/FastFloor/shader/ 
#      $<TARGET_FILE_DIR:FastFloor>/shader)

#add_custom_command(
#   TARGET FastFloor POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy
#      ${CMAKE_SOURCE_DIR}/test/input.txt
#      ${CMAKE_CURRENT_BINARY_DIR}/input.txt)

target_link_libraries(${PROJECT_NAME} 
   SDL2::SDL2 SDL2::SDL2main glm::glm GLEW::GLEW 
)

target_sources(${PROJECT_NAME} PRIVATE
#   "source/engine.cpp" 
#   "source/engine.h"
   "source/sdl2.h"
   "main.cpp"
)