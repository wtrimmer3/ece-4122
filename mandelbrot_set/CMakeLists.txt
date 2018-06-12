cmake_minimum_required(VERSION 3.10)
project(mandelbrot_set)

include_directories(lib)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/glfw)

add_executable(mandelbrot_set main.cpp glad.c shader.h)

#opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

target_link_libraries(
        mandelbrot_set
        glfw
        ${OPENGL_LIBRARIES}
        ${EXTRA_LIBS}
)