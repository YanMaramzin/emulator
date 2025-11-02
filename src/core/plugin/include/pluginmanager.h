#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <filesystem>
#include "pluginloader.h"


class PluginManager
{
public:
    bool loadPlugin(const std::filesystem::path &path);
    void unloadPlugin(const std::filesystem::path &path);
    bool loadPluginsFromFolder(const std::filesystem::path &pathFolder);
    void unloadAllPlugins();

private:
    std::unique_ptr<PluginLoader> createPluginLoader();
    std::unordered_map<std::filesystem::path, std::unique_ptr<PluginLoader>> m_loaders;
    std::unordered_map<std::filesystem::path, std::shared_ptr<IPlugin>> m_plugins;
};
