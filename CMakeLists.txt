cmake_minimum_required(VERSION 3.28)
project(emulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_subdirectory(src)

set(PLUGIN_SRC_DIR "${CMAKE_BINARY_DIR}/plugins")  # где собираются .so/.dll
set(PLUGIN_BIN_DIR "${CMAKE_BINARY_DIR}/bin/plugins")

file(GLOB_RECURSE PLUGIN_FILES
        "${PLUGIN_SRC_DIR}/*.so"
        "${PLUGIN_SRC_DIR}/*.dll"
)

message(INFO "${PLUGIN_FILES}")
if(PLUGIN_FILES)
# Создаём цель, которая копирует все плагины
add_custom_target(copy_plugins emulator
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PLUGIN_BIN_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PLUGIN_FILES}... ${PLUGIN_BIN_DIR}
        COMMENT "Copying plugins to ${PLUGIN_BIN_DIR}"
)
endif()