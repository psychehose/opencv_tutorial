cmake_minimum_required(VERSION 3.10)
project(blending_two_images)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clangd header 찾을 때

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})