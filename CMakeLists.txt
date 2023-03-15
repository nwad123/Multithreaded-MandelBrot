cmake_minimum_required(VERSION 3.25.1)

project(Multithreaded_Mandelbrot)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Mandelbrot)

target_include_directories(${PROJECT_NAME} PUBLIC Mandelbrot)

target_link_directories(${PROJECT_NAME} PRIVATE Mandelbrot)

target_link_libraries(${PROJECT_NAME} mandelbrot)