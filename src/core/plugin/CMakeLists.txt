
add_library(core.plugin)

target_sources(core.plugin
        PUBLIC
        FILE_SET CXX_MODULES FILES
        iplugin.ixx
        pluginmanager.ixx
        pluginloader.ixx
)

target_link_libraries(core.plugin PRIVATE core.logger)