cmake_minimum_required(VERSION 3.18)

project(FastFloor CXX)
message(STATUS ${PROJECT_NAME})

# find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME})

# target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

target_sources(${PROJECT_NAME} PRIVATE
"main.cpp"
)