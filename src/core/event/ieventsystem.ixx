module;
#include <functional>

export module core.ieventsystem;
import core.events;

export class IEventSystem {
public:
    virtual ~IEventSystem() = default;

    virtual void subscribePluginLoaded(std::function<void(const PluginLoadedEvent&)>) = 0;
    virtual void subscribePluginUnloaded(std::function<void(const PluginUnloadedEvent&)>) = 0;

    virtual void publishPluginLoaded(const PluginLoadedEvent &e) = 0;
    virtual void publishPluginUnloaded(const PluginUnloadedEvent &e) = 0;
};
