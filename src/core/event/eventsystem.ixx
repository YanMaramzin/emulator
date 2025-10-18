module;

#include <vector>
#include <functional>

export module core.eventsystem;

import core.events;
import core.ieventsystem;

export class EventSystem final : public IEventSystem {
public:
    void subscribePluginLoaded(std::function<void(const PluginLoadedEvent &)> callback) override {
        pluginLoadedCallbacks.push_back(callback);
    }

    void subscribePluginUnloaded(std::function<void(const PluginUnloadedEvent &)> callback) override {
        pluginUnloadedCallbacks.push_back(callback);
    }

    void publishPluginLoaded(const PluginLoadedEvent &e) override {
        for (auto &cb: pluginLoadedCallbacks)
            cb(e);
    }

    void publishPluginUnloaded(const PluginUnloadedEvent &e) override {
        for (auto &cb: pluginUnloadedCallbacks)
            cb(e);
    }

private:
    std::vector<std::function<void(const PluginLoadedEvent&)>> pluginLoadedCallbacks;
    std::vector<std::function<void(const PluginUnloadedEvent&)>> pluginUnloadedCallbacks;
};