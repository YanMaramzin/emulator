module;
#include <string>

export module core.event;

export enum class EventType {
    PluginLoaded,
    PluginUnloaded,
    DeviceConnected,
    DeviceDisconnected
    // позже добавим свои события
};

export struct Event {
    EventType type;
    std::string message; // простое поле для примера, можно расширять
};

