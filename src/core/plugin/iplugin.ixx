module;

#include <string>

export module core.iplugin;

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

    virtual std::string name() const = 0;
    virtual void initialize() = 0;
    virtual void shutdown() = 0;

    PluginState state() const noexcept { return m_state; }
private:
    PluginState m_state = PluginState::Uninitialized;
};