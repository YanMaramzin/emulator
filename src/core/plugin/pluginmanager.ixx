module;
#include <utility>
#include <vector>
#include <filesystem>
#include <memory>

export module core.pluginmanager;

import core.iplugin;
import core.pluginloader;
import core.logger.console;
import core.logger;
import core.ieventsystem;
import core.eventsystem;

struct ManagedPlugin {
    std::unique_ptr<IPlugin> instance;
    std::filesystem::path pluginPath;
};

export class PluginManager
{
public:
    explicit PluginManager(std::filesystem::path pluginDir);
    void registerPlugin(ManagedPlugin plugin);
    void loadAll();
    void initializeAll() const;
    void shutdownAll() const;

    // Managing Plugins
    void startPlugin(const std::string &name);
    void reloadPlugin(const std::string &name);
    void stopPlugin(const std::string &name);

private:
    [[nodiscard]] std::vector<std::filesystem::path> scanPlugins() const;
    std::filesystem::path m_pluginDir;
    PluginLoader loader;
    std::unique_ptr<ConsoleLogger> m_logger;
    std::vector<ManagedPlugin> m_plugins;
    std::shared_ptr<IEventSystem> m_eventSystem;
};

PluginManager::PluginManager(std::filesystem::path pluginDir) :
    m_pluginDir(std::move(pluginDir)),
    m_logger(std::make_unique<ConsoleLogger>()),
    m_eventSystem(std::make_shared<EventSystem>())
{
    m_logger->log(LogLevel::Info, "PluginManager initialized");
    loadAll();
    initializeAll();
    // публикуем событие
    m_eventSystem->publishPluginLoaded({ "BUS BUS"});
}

void PluginManager::registerPlugin(ManagedPlugin plugin)
{
    m_logger->log(LogLevel::Info, plugin.instance->metadata().name);
    m_plugins.push_back(std::move(plugin));
}

void PluginManager::loadAll()
{
    for (const auto &path : scanPlugins()) {
        auto pluginInstance = loader.load(path.string());
        if (!pluginInstance) {
            m_logger->log(LogLevel::Error, "Failed to load plugin: " + path.string());
            continue;
        }
        pluginInstance->setEventSystem(m_eventSystem);
        const auto meta = pluginInstance->metadata();
        m_logger->log(LogLevel::Info, meta.name);

        m_plugins.push_back({ std::move(pluginInstance), path });
    }
}

void PluginManager::initializeAll() const
{
    for (const auto &[instance, _] : m_plugins)
        instance->initialize();
}

void PluginManager::shutdownAll() const {
    for (const auto &[instance, _] : m_plugins)
        instance->shutdown();
}

void PluginManager::startPlugin(const std::string &name)
{
    m_logger->log(LogLevel::Info, "Starting plugin " + name);
    for (const auto &[instance, pluginPath] : m_plugins) {
        if (instance->metadata().name != name)
            continue;

        instance->initialize();
        m_logger->log(LogLevel::Info, "Plugin {} initialized manually" + name);
        return;
    }

    m_logger->log(LogLevel::Warning, "Plugin {} not found" + name);
}

void PluginManager::reloadPlugin(const std::string &name)
{
    stopPlugin(name);
    for (auto &[instance, pluginPath] : m_plugins) {
        if (instance->metadata().name != name)
            continue;

        if (auto newPlugin = loader.load(pluginPath)) {
            instance = std::move(newPlugin);
            startPlugin(name);
            m_logger->log(LogLevel::Info, "Plugin successfully reloaded: " + name);
        } else {
            m_logger->log(LogLevel::Error, "Failed to reload plugin: " + name);
        }
    }

    m_logger->log(LogLevel::Warning, "Plugin not found for reload: " + name);
}

void PluginManager::stopPlugin(const std::string &name)
{
    m_logger->log(LogLevel::Info, "Stopping plugin " + name);
    for (auto &[instance, pluginPath] : m_plugins) {
        if (instance->metadata().name != name)
            continue;

        instance->shutdown();
        m_logger->log(LogLevel::Info, "Plugin {} shutdown manually" + name);
        return;
    }

    m_logger->log(LogLevel::Warning, "Plugin {} not found" + name);
}

std::vector<std::filesystem::path> PluginManager::scanPlugins() const
{
    std::vector<std::filesystem::path> pluginsFiles;

    if (!std::filesystem::exists(m_pluginDir)) {
        m_logger->log(LogLevel::Error, "Plugin directory not found");
        return pluginsFiles;
    }

    for (const auto &entry : std::filesystem::directory_iterator(m_pluginDir)) {
        if (!entry.is_regular_file())
            continue;

        const auto &path = entry.path();
#if defined(_WIN32)
        if (path.extension() != ".dll")
            continue;
#else
        if (path.extension() != ".so")
            continue;
#endif
        m_logger->log(LogLevel::Info, "Found plugin file " + path.string());
        pluginsFiles.push_back(path);
    }

    return pluginsFiles;
}

export PluginManager pluginManager {std::filesystem::path("../../bin/plugins")};