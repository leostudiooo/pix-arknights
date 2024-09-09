cmake_minimum_required(VERSION 3.10)
project(Pixnights)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 平台检测和设置
if(APPLE)
    set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib/cmake/SFML")
    find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)
elseif(WIN32)
    set(SFML_DIR "C:/sfml/2.6.1/lib/cmake/SFML")
    set(SFML_INCLUDE_DIR "C:/sfml/2.6.1/include")
    set(SFML_LIBRARY_DIR "C:/sfml/2.6.1/lib")
    find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)
elseif(MINGW)
    set(SFML_DIR "C:/sfml/2.6.1-gcc/lib/cmake/SFML")
    set(SFML_INCLUDE_DIR "C:/sfml/2.6.1-gcc/include")
    set(SFML_LIBRARY_DIR "C:/sfml/2.6.1-gcc/lib")
    find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)
endif()

# 调试 SFML
message(STATUS "SFML found: ${SFML_FOUND}")

# 收集源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 添加可执行文件
add_executable(Pixnights ${SOURCES})

# 添加头文件目录
target_include_directories(Pixnights PUBLIC ${SFML_INCLUDE_DIRS} "src/include")

# 添加链接库
target_link_libraries(Pixnights sfml-graphics sfml-window sfml-system sfml-audio)

# gcc libstdc++库
if(MINGW)
    target_link_libraries(Pixnights -static-libstdc++)
endif()

if(MSVC)
    # set working directory
    set_target_properties(Pixnights PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
    target_compile_options(Pixnights PRIVATE /utf-8)
endif()