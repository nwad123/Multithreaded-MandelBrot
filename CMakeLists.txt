cmake_minimum_required(VERSION 3.22.1)

project(Multithreaded_Mandelbrot)

# generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# call the executable the same as the project name
add_executable(${PROJECT_NAME} main.cpp)

# Add Mandelbrot library
add_subdirectory(Mandelbrot)

target_include_directories(${PROJECT_NAME} PUBLIC Mandelbrot)

target_link_directories(${PROJECT_NAME} PRIVATE Mandelbrot)

target_link_libraries(${PROJECT_NAME} mandelbrot)
