
add_library(core.logger)

target_sources(core.logger
    PUBLIC
        FILE_SET CXX_MODULES FILES
    logger.ixx
    consolelogger.ixx
)

target_compile_features(core.logger PUBLIC cxx_std_20)
target_compile_options(core.logger PUBLIC -fprebuilt-module-path=<путь>)


if (BUILD_TEST)
    add_subdirectory(tests)
endif ()