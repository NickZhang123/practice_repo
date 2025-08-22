cmake_minimum_required(VERSION 3.14.1)  
project(test_cpp)

# 编译处理
set(CMAKE_CXX_COMPILER "/usr/local/gcc10/bin/g++")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O0 -std=c++17")
message(STATUS ${CMAKE_CXX_FLAGS})


# 目标
add_executable(cpp_prac main.cpp)

# 源文件
file(GLOB SRC *.cpp)
message(STATUS "all_src[" ${SRC} "]") 
target_sources(cpp_prac PRIVATE ${SRC})

# 头文件
target_include_directories(cpp_prac PRIVATE "/usr/local/gcc10/include")

# 链接库
target_link_directories(cpp_prac PRIVATE "/usr/local/gcc10/lib/gcc" "/usr/local/gcc10/lib64")
target_link_libraries(cpp_prac PRIVATE pthread)

