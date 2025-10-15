module;
#include <vector>
#include <filesystem>
#include <memory>

export module core.pluginmanager;

import core.iplugin;
import core.pluginloader;
import core.logger.console;
import core.logger;

export class PluginManager
{
public:
    explicit PluginManager(const std::filesystem::path &pluginDir);
    void registerPlugin(std::unique_ptr<IPlugin> plugin);
    void initializeAll() const;
    void shutdownAll() const;


    // Managing Plugins
    void startPlugin(const std::string &name);
    void reloadPlugin(const std::string &name);
    void stopPlugin(const std::string &name);

private:
    std::vector<std::filesystem::path> scanPlugins() const;
    std::filesystem::path m_pluginDir;
    PluginLoader loader;
    std::unique_ptr<ConsoleLogger> m_logger;
    std::vector<std::unique_ptr<IPlugin>> m_plugins;
};

PluginManager::PluginManager(const std::filesystem::path &pluginDir) :
    m_pluginDir(pluginDir),
    m_logger(std::make_unique<ConsoleLogger>())
{
    m_logger->log(LogLevel::Info, "PluginManager initialized");
    for (const auto pluginsPath = scanPlugins(); const auto &pluginPath: pluginsPath) {
        auto plugin = loader.load(pluginPath);
        if (!plugin) {
            m_logger->log(LogLevel::Error, "Failed to load plugin " + pluginPath.string());
            continue;
        }
        registerPlugin(std::move(plugin));
    }

    initializeAll();
}

void PluginManager::registerPlugin(std::unique_ptr<IPlugin> plugin)
{
    m_logger->log(LogLevel::Info, "Registering plugin " + plugin->name());
    m_plugins.push_back(std::move(plugin));
}

void PluginManager::initializeAll() const
{
    for (const auto &plugin : m_plugins)
        plugin->initialize();
}

void PluginManager::shutdownAll() const {
    for (const auto &plugin : m_plugins)
        plugin->shutdown();
}

void PluginManager::startPlugin(const std::string &name)
{
    m_logger->log(LogLevel::Info, "Starting plugin " + name);
    for (auto &plugin: m_plugins) {
        if (plugin->name() == name) {
            try {
                plugin->initialize();
                m_logger->log(LogLevel::Info, "Plugin {} initialized manually" + name);
            } catch (const std::exception &e) {
                m_logger->log(LogLevel::Error, "Failed to initialize plugin" + name + e.what());
            }
            return;
        }
    }
    m_logger->log(LogLevel::Warning, "Plugin {} not found" + name);
}

void PluginManager::reloadPlugin(const std::string &name)
{
    // Logger::instance().log(LogLevel::Info, "Reloading plugin: " + name);

    stopPlugin(name);

    // Находим плагин и перезагружаем через loader
    // auto pluginPtr = findPlugin(name);
    // if (!pluginPtr) {
        // Logger::instance().log(LogLevel::Error, "Cannot reload: plugin not found: " + name);
        // return;
    // }

    // std::filesystem::path pluginPath = loader.libraryPathOf(name);
    // auto newPlugin = loader.load(pluginPath);

    // if (newPlugin) {
        // *pluginPtr = std::move(newPlugin);
        // startPlugin(name);
        // Logger::instance().log(LogLevel::Info, "Plugin successfully reloaded: " + name);
    // } else {
        // Logger::instance().log(LogLevel::Error, "Failed to reload plugin: " + name);
    // }
}

void PluginManager::stopPlugin(const std::string &name)
{
    m_logger->log(LogLevel::Info, "Stopping plugin " + name);
    for (auto &plugin : m_plugins) {
        if (plugin->name() == name) {
            try {
                plugin->shutdown();
                m_logger->log(LogLevel::Info, "Plugin {} shutdown manually" + name);
            } catch (const std::exception& e) {
                m_logger->log(LogLevel::Error, "Failed to shutdown plugin" + name + e.what());
            }
            return;
        }
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

export PluginManager pluginManager {std::filesystem::path("../../plugins")};