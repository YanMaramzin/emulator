module;
#include <vector>
#include <filesystem>
#include <iostream>
#include <memory>

export module core.pluginmanager;

import core.iplugin;
import core.pluginloader;

export class PluginManager
{
public:
    PluginManager(const std::filesystem::path &pluginDir);
    void registerPlugin(std::unique_ptr<IPlugin> plugin);
    void initializeAll() const;
    void shutdownAll() const;
private:
    std::vector<std::filesystem::path> scanPlugins() const;
    std::filesystem::path m_pluginDir;
    PluginLoader loader;
    std::vector<std::unique_ptr<IPlugin>> m_plugins;
};

PluginManager::PluginManager(const std::filesystem::path &pluginDir) : m_pluginDir(pluginDir)
{
    std::cout << "PLUGINMANGER " << m_pluginDir.string() << std::endl;
    for (const auto pluginsPath = scanPlugins(); const auto &pluginPath: pluginsPath) {
        std::cout << pluginPath;
        auto plugin = loader.load(pluginPath);
        registerPlugin(std::move(plugin));
    }

    initializeAll();
}

void PluginManager::registerPlugin(std::unique_ptr<IPlugin> plugin)
{
    m_plugins.push_back(std::move(plugin));
}

void PluginManager::initializeAll() const {
    for (const auto &plugin : m_plugins)
        plugin->initialize();
}

void PluginManager::shutdownAll() const {
    for (const auto &plugin : m_plugins)
        plugin->shutdown();
}

std::vector<std::filesystem::path> PluginManager::scanPlugins() const
{
    std::vector<std::filesystem::path> pluginsFiles;

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
        pluginsFiles.push_back(path);
    }

    return pluginsFiles;
}

export PluginManager pluginManager {"../../plugins"};