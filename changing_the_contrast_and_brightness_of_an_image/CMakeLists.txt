cmake_minimum_required(VERSION 3.10)
project(changing_the_contrast_and_brightness_of_an_image)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clangd header 찾을 때

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} changing_contrast_brightness_image.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})