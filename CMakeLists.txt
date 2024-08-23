cmake_minimum_required(VERSION 3.10)
project(HelloSFML)

# 找到SFML库
set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/sfml/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# 添加可执行文件
add_executable(HelloSFML main.cpp)

# 链接SFML库
target_link_libraries(HelloSFML sfml-graphics sfml-window sfml-system)
