project(core.plugin)

add_library(${PROJECT_NAME} STATIC
    include/iplugin.h
    include/ipluginloaderimpl.h
    include/pluginloader.h
    src/pluginloader.cpp
    include/pluginmanager.h
    src/pluginmanager.cpp
    include/pluginloaderlinux.h
    src/pluginloaderlinux.cpp
    include/pluginloaderwindows.h
    src/pluginloaderwindows.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    core.event
PRIVATE
    core.logger
)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml)
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Gui
        Qt6::Qml
)
