
add_library(core.logging)

target_sources(core.logging
    PUBLIC
        FILE_SET CXX_MODULES FILES
    logger.ixx
)

if (BUILD_TEST)
    add_subdirectory(tests)
endif ()