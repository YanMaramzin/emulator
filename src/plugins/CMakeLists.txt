set(BIN_DIR "${CMAKE_BINARY_DIR}/bin")
set(PLUGIN_DIR "${BIN_DIR}/plugins")

## Для исполняемых файлов
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Для динамических библиотек (.dll/.so)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PLUGIN_DIR}) # для .lib/.a если нужно

add_subdirectory(mainwindow)
add_subdirectory(testplugin)
