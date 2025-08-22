project(day01)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${PROJECT_NAME} OBJECT ${SOURCE_FILES})

# 增加头文件引用
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}     # 暴露自己的头文件
    ${OpenCV_INCLUDE_DIRS}
)

# 增加库引用地址
target_link_directories(${PROJECT_NAME} PUBLIC 
    ${OpenCV_LIBS}
)   