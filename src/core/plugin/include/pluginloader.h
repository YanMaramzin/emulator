#pragma once
#include <memory>
#include "ipluginloaderimpl.h"

class IPlugin;

class PluginLoader
{
public:
    explicit PluginLoader(std::unique_ptr<IPluginLoaderImpl> impl);

    std::shared_ptr<IPlugin> load(const std::string &path);
    void unload();
    bool isLoaded() const;
private:
    std::unique_ptr<IPluginLoaderImpl> m_impl;
};
