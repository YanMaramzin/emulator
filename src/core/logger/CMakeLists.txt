project(core.logger)

add_library(${PROJECT_NAME} STATIC
    include/logger.h
    src/logger.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (BUILD_TEST)
    add_subdirectory(tests)
endif ()