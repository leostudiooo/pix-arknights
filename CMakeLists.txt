cmake_minimum_required(VERSION 3.10)
project(Pixnights)

if(MACOSX)
	set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib/cmake/SFML")
	find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
else()
	find_package(SFML COMPONENTS graphics window system REQUIRED)
endif()

# 添加可执行文件
add_executable(Pixnights main.cpp)

# 链接SFML库
target_link_libraries(Pixnights sfml-graphics sfml-window sfml-system)
