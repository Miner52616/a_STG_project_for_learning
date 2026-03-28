cmake_minimum_required(VERSION 3.16)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 20)

# 你的头文件目录
include_directories(include)

# 自动收集所有 cpp
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# 可执行文件
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(main ${SRC_FILES})

target_precompile_headers(main PRIVATE
    <SFML/Graphics.hpp>
    <vector>
    <memory>
)

# SFML 路径（你是 msys2）
set(SFML_DIR "C:/msys64/mingw64/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(main
    SFML::Graphics
    SFML::Window
    SFML::System
)