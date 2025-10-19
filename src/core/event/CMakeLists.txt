add_library(core.event)

target_sources(core.event
        PUBLIC
        FILE_SET CXX_MODULES FILES
        events.ixx
        eventsystem.ixx
        ieventsystem.ixx
)

target_link_libraries(core.event PRIVATE core.object)

set_target_properties(core.event PROPERTIES POSITION_INDEPENDENT_CODE ON)