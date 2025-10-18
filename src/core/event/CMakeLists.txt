add_library(core.event)

target_sources(core.event
        PUBLIC
        FILE_SET CXX_MODULES FILES
        events.ixx
        eventsystem.ixx
        ieventsystem.ixx
)