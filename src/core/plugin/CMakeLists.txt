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
PRIVATE
    core.logger
)