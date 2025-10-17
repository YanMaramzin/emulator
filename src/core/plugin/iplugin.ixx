module;

#include <string_view>

export module core.iplugin;

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

    [[nodiscard]] PluginState state() const noexcept { return m_state; }
private:
    PluginState m_state = PluginState::Uninitialized;
};

