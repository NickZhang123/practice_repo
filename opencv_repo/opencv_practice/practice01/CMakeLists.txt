cmake_minimum_required(VERSION 3.10)
project(demo)

set(CMAKE_CXX_STANDARD 17)

# 指定OpenCV安装路径（/usr/local）
set(OpenCV_DIR "/usr/local/lib/cmake/opencv4")

# 查找OpenCV
find_package(OpenCV REQUIRED)

# 打印调试信息
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

add_subdirectory(day01_09)

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 包含头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${OpenCV_INCLUDE_DIRS}
)

# 链接 OpenCV 库
target_link_libraries(${PROJECT_NAME} PRIVATE  
    ${OpenCV_LIBS}
    day01
)