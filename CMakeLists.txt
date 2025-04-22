cmake_minimum_required(VERSION 3.10)
project(Minecraft2)

set(CMAKE_CXX_STANDARD 17)

# Source files
file(GLOB SRC_FILES
    src/*.cpp
)

add_executable(minecraft2 ${SRC_FILES})

find_package(OpenGL REQUIRED)
find_path(SDL2_INCLUDE_DIR SDL.h PATH_SUFFIXES SDL2)
find_library(SDL2_LIBRARY SDL2)

include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(minecraft2
${SDL2_LIBRARY}
GLEW 
OpenGL::GL)
