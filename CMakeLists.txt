cmake_minimum_required(VERSION 3.19)
project(Cube_Game)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

add_executable(Cube_Game
        src/main.cpp
        src/glad.c src/render/Shader.cpp src/render/Shader.hpp src/render/Camera.cpp src/render/Camera.hpp src/Direction.hpp include/stb_image.h src/objects/Object.hpp src/objects/Cube.cpp src/objects/Cube.hpp src/models/cube.hpp)

target_include_directories(Cube_Game
        PUBLIC include)

target_link_libraries(Cube_Game
        PUBLIC glfw)