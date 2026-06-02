cmake_minimum_required(VERSION 3.21)

project(SFMLGame)

set(CMAKE_CXX_STANDARD 20)

#////CMAKE寻找依赖库根目录路径，需编译请自行重新修改路径！////
set(CMAKE_PREFIX_PATH "C:/msys64/mingw64")


# ======================
# 项目结构
# ======================

# 头文件目录
include_directories(include)

# 收集 cpp
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# 可执行文件输出到项目根目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# 创建可执行文件
add_executable(main ${SRC_FILES})

# 预编译头加快编译速度
target_precompile_headers(main PRIVATE
    <SFML/Graphics.hpp>
    <vector>
    <memory>
)

# ======================
# SFML
# ======================

#////SFML路径，需编译请自行重新修改路径！////
set(SFML_DIR "C:/msys64/mingw64/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)


target_link_libraries(main PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# ======================
# Lua
# ======================

#////Lua安装路径，需编译请自行重新修改路径！////
set(LUA_INCLUDE_DIR "C:/msys64/mingw64/include")
set(LUA_LIBRARY "C:/msys64/mingw64/lib/liblua.dll.a")

target_include_directories(main PRIVATE ${LUA_INCLUDE_DIR})

target_link_libraries(main PRIVATE ${LUA_LIBRARY})

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:main>
        $<TARGET_FILE_DIR:main>
    COMMAND_EXPAND_LISTS
)