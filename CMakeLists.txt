# set to clang (nicer warnings)
if(EXISTS "/usr/bin/clang" AND EXISTS "/usr/bin/clang++")
  SET(CMAKE_C_COMPILER "/usr/bin/clang")
  SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
endif()

cmake_minimum_required(VERSION 3.22.1)

project(Multithreaded_Mandelbrot)

# generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set warning flags
message(STATUS "Adding warning flags")
if (MSVC)
  add_compile_options(/W4)
else ()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# set optimization flags
if (NOT DEFINED RELEASE)
  message(STATUS "Debug/Release not specified. Setting to debug by default...")
  set(RELEASE false)
endif()

# setting release and debug flags
if (RELEASE)
  message(STATUS "Adding optimization options")
  if (MSVC)
    add_compile_options(/O2)
  else ()
    add_compile_options(-O3 -march=native -m64)
  endif()
else()
  message(STATUS "Adding debug options")
  if (MSVC)
    add_compile_options(/Zi)
  else ()
    add_compile_options(-g3 -O0)
  endif()
endif()

# call the executable the same as the project name
add_executable(${PROJECT_NAME} main.cpp)

# Add Threadpool library
add_subdirectory(Threadpool)

target_include_directories(${PROJECT_NAME} PUBLIC Threadpool)

target_link_directories(${PROJECT_NAME} PRIVATE Threadpool)

target_link_libraries(${PROJECT_NAME} Threadpool)

# Add Mandelbrot library
add_subdirectory(Mandelbrot)

target_include_directories(${PROJECT_NAME} PUBLIC Mandelbrot)

target_link_directories(${PROJECT_NAME} PRIVATE Mandelbrot)

target_link_libraries(${PROJECT_NAME} mandelbrot)
