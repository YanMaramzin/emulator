
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml)

add_library(mainwindow SHARED)
target_sources(mainwindow
        PUBLIC
        FILE_SET CXX_MODULES FILES
        mainwindow.ixx
)

qt_add_qml_module(mainwindow
    URI mainwindow
    VERSION 1.0
    QML_FILES qml/MainWindow.qml
)

target_link_libraries(mainwindow
PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
        Qt6::Qml
        core.plugin)