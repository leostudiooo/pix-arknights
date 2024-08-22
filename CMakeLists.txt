cmake_minimum_required(VERSION 3.5)

# 设置项目名
project(MyRaylibProject)

# 添加源文件
add_executable(${PROJECT_NAME} main.cpp)

# 找到并包含Raylib头文件
find_path(RL_INCLUDE_DIR NAMES raylib.h PATHS /opt/homebrew/opt/raylib/include)
include_directories(${RL_INCLUDE_DIR})

# 找到并链接Raylib库
find_library(RL_LIBRARY NAMES raylib PATHS /opt/homebrew/opt/raylib/lib)
target_link_libraries(${PROJECT_NAME} ${RL_LIBRARY})

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
add_compile_options(-std=c++11)