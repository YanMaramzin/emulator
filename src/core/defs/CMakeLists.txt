add_library(core.object)

target_sources(core.object
        PUBLIC
        FILE_SET CXX_MODULES FILES
        object.ixx
)

