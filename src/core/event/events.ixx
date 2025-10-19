export module core.events;

export struct PluginLoadedEvent {
    const char *name;
};

export struct PluginUnloadedEvent {
    const char *name;
};

export struct MyEvent {
    int value;
};