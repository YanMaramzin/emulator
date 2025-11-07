project(device_emulator)

find_package(Qt6 REQUIRED COMPONENTS  Gui)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC core.plugin)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt6::Gui
)
