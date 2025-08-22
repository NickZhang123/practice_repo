cmake_minimum_required(VERSION 3.16)
project(practice_opencv)

# 指定OpenCV安装路径（/usr/local）
set(OpenCV_DIR "/usr/local/lib/cmake/opencv4")

# 查找OpenCV
find_package(OpenCV REQUIRED)

# 打印调试信息
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

add_subdirectory(opencv_utils)
# add_subdirectory(practice01)

