add_library(testPlugin SHARED)

target_sources(testPlugin
        PUBLIC
        FILE_SET CXX_MODULES FILES
        testplugin.ixx
)

target_link_libraries(testPlugin PRIVATE core.plugin core.event)
