cmake_minimum_required(VERSION 3.16)

# 设置生成器为MinGW Makefiles
# set(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)   -- 不会生效

# 设置编译工具路径          -- 必须使用缓存，且强制更新缓存
set(TOOLCHAIN_DIR "D:/QT/QT6/Tools/mingw1310_64" CACHE PATH "MinGW path")
set(CMAKE_C_COMPILER "${TOOLCHAIN_DIR}/bin/gcc.exe" CACHE FILEPATH "C compiler" FORCE)
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_DIR}/bin/g++.exe" CACHE FILEPATH "C++ compiler" FORCE)   # FORCE,强制更新缓存

# 设置qt安装路径
#set(Qt6_DIR "D:/QT/QT6/6.8.3/mingw_64/lib/cmake/Qt6")                       # Qt6_DIR是CMake用于查找Qt6包的特殊变量
# set(CMAKE_PREFIX_PATH "D:/QT/QT6/6.8.3/mingw_64")  # 指向Qt安装目录
set(CMAKE_PREFIX_PATH "D:/QT/QT6/6.8.3/mingw_64" CACHE PATH "Qt path" FORCE)

project(practice_new VERSION 0.1 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# 查找Qt包
find_package(Qt6 REQUIRED COMPONENTS Quick)

# 启用自动处理MOC、UIC和RCC文件
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/z-out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/z-out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/z-out/bin)

# 设置Qt标准项目配置
qt_standard_project_setup(REQUIRES 6.8)

# 添加可执行文件
qt_add_executable(${PROJECT_NAME}
    main.cpp
)

# 编译选项 - 只在MinGW下使用这些选项
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
    target_compile_definitions(${PROJECT_NAME} PRIVATE QT_DEBUG)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /Zc:__cplusplus /Zi)
    target_compile_definitions(${PROJECT_NAME} PRIVATE QT_DEBUG)
endif()

# 添加QML模块
qt_add_qml_module(${PROJECT_NAME}
    URI practice_new
    VERSION 1.0
    RESOURCES a.qrc
    QML_FILES 
        qml/Main.qml
        qml/Test1.qml
        qml/PasswordInput.qml
        qml/Test2.qml
        qml/Layout.qml
        qml/ListViewTest.qml
        qml/PathViewTest.qml
)

# 设置目标属性
set_target_properties(${PROJECT_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apppractice_new
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 链接库
target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Quick
)

# 包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 安装配置
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
