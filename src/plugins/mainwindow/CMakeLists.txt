project(mainwindowplugin)


find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME} SHARED
    include/mainwindowplugin.h
    src/mainwindowplugin.cpp
    include/tabmodel.h
    src/tabmodel.cpp
)

qt_add_resources(${PROJECT_NAME}
    PREFIX /plugins/MainWindow
    FILES qml/MainWindow.qml
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        core.plugin
        core.event
        Qt6::Core
        Qt6::Quick
        Qt6::Gui
        Qt6::Qml
)
