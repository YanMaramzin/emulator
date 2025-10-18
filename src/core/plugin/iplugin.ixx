module;

#include <memory>
#include <string_view>

export module core.iplugin;
import core.ieventsystem;

export struct PluginMetadata {
    std::string_view id;
    std::string_view name;
    // std::string version;
    // std::string author;
    // std::string description;
    // std::string apiVersion;
    //std::vector<std::string> dependencies;
};

export enum PluginState {
    Uninitialized,
    Initialized,
    Running,
    Stopped
};

export class IPlugin
{
public:
    virtual ~IPlugin() = default;

    virtual void initialize() = 0;
    virtual void shutdown() = 0;
    virtual const PluginMetadata metadata() const = 0;
    virtual void setEventSystem(const std::shared_ptr<IEventSystem> &es) { m_eventSystem = es; }

    [[nodiscard]] PluginState state() const noexcept { return m_state; }

protected:
    [[nodiscard]] std::shared_ptr<IEventSystem> eventSystem() const { return m_eventSystem.lock(); }

private:
    PluginState m_state {Uninitialized};
    std::weak_ptr<IEventSystem> m_eventSystem;
};

