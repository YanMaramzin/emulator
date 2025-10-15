
add_library(core.logger)

target_sources(core.logger
    PUBLIC
        FILE_SET CXX_MODULES FILES
    logger.ixx
    consolelogger.ixx
)

if (BUILD_TEST)
    add_subdirectory(tests)
endif ()