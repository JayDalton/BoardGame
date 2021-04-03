cmake_minimum_required(VERSION 3.18)

project(DontWorry CXX)
message(STATUS ${PROJECT_NAME})

# find_package(fmt CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
# find_package(glfw3 CONFIG REQUIRED)
find_package(SFML COMPONENTS system window network graphics audio main CONFIG REQUIRED)

add_executable(${PROJECT_NAME})

# target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
# target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-network sfml-graphics sfml-audio)

target_sources(${PROJECT_NAME} PRIVATE
"main.cpp"
)