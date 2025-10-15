

add_executable(device_emulator main.cpp)

target_link_libraries(device_emulator PUBLIC core.logger core.plugin)