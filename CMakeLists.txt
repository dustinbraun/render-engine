cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(ogl)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(ogl src/main.cpp src/scene.cpp src/stb_image.cpp src/glew.c)

target_link_libraries(ogl PRIVATE glm::glm OpenGL::GL ${SDL2_LIBRARIES})

add_subdirectory(third_party)
