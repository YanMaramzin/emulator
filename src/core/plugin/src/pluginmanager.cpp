#include <pluginmanager.h>
#include <iostream>
#include "pluginloaderlinux.h"
#include <logger.h>

PluginManager::PluginManager() {
    m_context.bus = std::make_shared<EventBus>();
}

bool PluginManager::loadPlugin(const std::filesystem::path &path) {

    Logger::log(LogLevel::Info, "Current filepath: " + path.string());
    if (m_loaders.contains(path))
        m_loaders[path]->unload();

    auto loader = createPluginLoader();
    auto plugin = loader->load(path);
    if (!plugin) {
        Logger::log(LogLevel::Warning,"Failed to load plugin: " + path.string());
        return false;
    }

    Logger::log(LogLevel::Info,"Load plugin: " + path.string());
    m_loaders[path] = std::move(loader);
    m_plugins[path] = std::move(plugin);

    return true;
}

void PluginManager::unloadPlugin(const std::filesystem::path &path) {
    if (m_loaders.contains(path)) {
        m_loaders[path]->unload();
        m_loaders.erase(path);
        m_plugins.erase(path);
    }
}

bool PluginManager::loadPluginsFromFolder(const std::filesystem::path &pathFolder) {
    if (!std::filesystem::exists(pathFolder) || !std::filesystem::is_directory(pathFolder)) {
        std::cerr << "Folder does not exist or is not a directory: " << pathFolder << "\n";
        return false;
    }

    bool allLoaded = true;

    for (const auto &entry: std::filesystem::directory_iterator(pathFolder)) {
        if (!entry.is_regular_file())
            continue;
        const auto &path = entry.path();
        std::cout << "PATH" << path << "\n";

        // Поддержка расширений
#ifdef _WIN32
        if (path.extension() != ".dll")
            continue;
#else
        if (path.extension() != ".so")
            continue;
#endif

        if (!loadPlugin(path.string())) {
            // loadPlugin всё ещё принимает string
            std::cerr << "Failed to load plugin: " << path << "\n";
            allLoaded = false;
        }
    }

    return allLoaded;
}

void PluginManager::unloadAllPlugins() {
    for (auto& [_, loader] : m_loaders)
        loader->unload();

    m_loaders.clear();
    m_plugins.clear();
}

void PluginManager::initializeAll() {
    for (auto &pl : m_plugins)
        pl.second->initialize(m_context);
}

std::unique_ptr<PluginLoader> PluginManager::createPluginLoader() {
#ifdef _WIN32
    return std::make_unique<PluginLoader>(std::make_unique<PluginLoaderWindows>());
#else
    return std::make_unique<PluginLoader>(std::make_unique<PluginLoaderLinux>());
#endif
}
