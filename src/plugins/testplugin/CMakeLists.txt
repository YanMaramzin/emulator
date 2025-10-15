add_library(testPlugin SHARED)

target_sources(testPlugin
        PUBLIC
        FILE_SET CXX_MODULES FILES
        testplugin.ixx
)
target_link_libraries(testPlugin PRIVATE core.plugin)

set_target_properties(testPlugin PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)