project(core.event)

add_library(${PROJECT_NAME} STATIC
    include/eventbus.h
    src/eventbus.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(core.event PRIVATE core.logger)

if (BUILD_TEST)
    add_subdirectory(tests)
endif ()