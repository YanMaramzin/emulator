module;
#include <filesystem>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

export module core.pluginloader;

import core.iplugin;

export class PluginLoader
{
public:
    ~PluginLoader() { unloadAll(); }

    std::unique_ptr<IPlugin> load(const std::string &path);
    void unloadAll();
private:
    // ConsoleLogger m_consoleLogger;
#if defined(_WIN32)
    std::vector<HMODULE> m_handles;
#else
    std::vector<void*> m_handles;
#endif
};

std::unique_ptr<IPlugin> PluginLoader::load(const std::string &path)
{
    #if defined(_WIN32)
        auto handle = LoadLibraryA(path.c_str());
        if (!handle)
            return nullptr;
            // m_consoleLogger.log(LogLevel::Info, std::string("Failed to load plugin:"));
        auto createFunc = reinterpret_cast<IPlugin*(*)()>(GetProcAddress(handle, "createPlugin"));
        if (!createFunc)
            FreeLibrary(handle);
    #else
        void *handle = dlopen(path.c_str(), RTLD_NOW);
        if (!handle)
            return nullptr;
        auto createFunc = reinterpret_cast<IPlugin*(*)()>(dlsym(handle, "createPlugin"));
        if (!createFunc)
            dlclose(handle);
    #endif

    m_handles.push_back(handle);
    return std::unique_ptr<IPlugin>(createFunc());
}

void PluginLoader::unloadAll()
{
    for (auto handle : m_handles) {
        #if defined(_WIN32)
            FreeLibrary(handle);
        #else
            dlclose(handle);
        #endif
    }
    m_handles.clear();
}

