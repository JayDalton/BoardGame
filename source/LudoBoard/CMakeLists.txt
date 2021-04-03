cmake_minimum_required(VERSION 3.18)

project(LudoBoard CXX)
message(STATUS ${PROJECT_NAME})

find_package(Corrade REQUIRED Main)
find_package(Magnum REQUIRED 
    GL 
    MeshTools 
    Primitives 
    Shaders 
    Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(${PROJECT_NAME} WIN32)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Corrade::Main
    Magnum::Application
    Magnum::GL
    Magnum::Magnum
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::Shaders)

target_sources(${PROJECT_NAME} PRIVATE
"MagnumApp.cpp"
"MagnumApp.h"
"main.cpp"
)