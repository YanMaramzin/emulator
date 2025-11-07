project(pluginmanagerui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml)

add_library(${PROJECT_NAME}
        SHARED
        pluginmodel.h
        pluginmanageruiplugin.cpp
        pluginmanageruiplugin.h
)

qt_add_resources(${PROJECT_NAME}
        PREFIX /plugins/PluginManagerUI
        FILES qml/PluginManager.qml
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Qml
        core.plugin
)