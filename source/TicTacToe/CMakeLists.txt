cmake_minimum_required(VERSION 3.20)

project(TicTacToe CXX)
message(STATUS ${PROJECT_NAME})

add_executable(${PROJECT_NAME}) # WIN32

target_link_libraries(${PROJECT_NAME} 
    
)

target_sources(${PROJECT_NAME} PRIVATE
   "main.cpp"
)