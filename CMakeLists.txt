cmake_minimum_required(VERSION 3.16)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:/msys64/mingw64")

# 头文件目录（sol2 也放这里）
include_directories(include)

# 自动收集 cpp
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# 可执行文件输出到项目根目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# 创建程序
add_executable(main ${SRC_FILES})

# 预编译头
target_precompile_headers(main PRIVATE
    <SFML/Graphics.hpp>
    <vector>
    <memory>
)

# ======================
# ✅ SFML
# ======================
set(SFML_DIR "C:/msys64/mingw64/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)


target_link_libraries(main PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# ======================
# ✅ Lua（加在这里）
# ======================
# Lua 路径（MSYS2）
set(LUA_INCLUDE_DIR "C:/msys64/mingw64/include")
set(LUA_LIBRARY "C:/msys64/mingw64/lib/liblua.dll.a")

target_include_directories(main PRIVATE ${LUA_INCLUDE_DIR})

target_link_libraries(main PRIVATE ${LUA_LIBRARY})