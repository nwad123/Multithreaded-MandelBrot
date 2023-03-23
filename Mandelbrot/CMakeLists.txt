cmake_minimum_required(VERSION 3.22.1)

project(mandelbrot)

add_library(mandelbrot mandelbrot.h mandelbrot.cpp)

# Add Threadpool library as a sub library
add_subdirectory(Threadpool)

target_include_directories(${PROJECT_NAME} PUBLIC Threadpool)

target_link_directories(${PROJECT_NAME} PRIVATE Threadpool)

target_link_libraries(${PROJECT_NAME} Threadpool)
