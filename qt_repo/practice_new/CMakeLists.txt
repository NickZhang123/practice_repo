cmake_minimum_required(VERSION 3.16)

project(practice_new VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

set(CMAKE_AUTORCC ON)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(apppractice_new
    main.cpp
)

qt_add_qml_module(apppractice_new
    URI practice_new
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES a.qrc
        QML_FILES  Test1.qml
        QML_FILES PasswordInput.qml
        QML_FILES Test2.qml
        QML_FILES layout.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apppractice_new PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apppractice_new
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apppractice_new
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS apppractice_new
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
