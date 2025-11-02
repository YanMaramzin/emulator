#pragma once
#include "ipluginloaderimpl.h"

using CreatePluginFunc = IPlugin* (*)();
using DestroyPluginFunc = void (*)(IPlugin*);

class PluginLoaderLinux final : public IPluginLoaderImpl
{
public:
    ~PluginLoaderLinux() override;

    std::shared_ptr<IPlugin> load(const std::string &path) override;

    void unload() override;

    bool isLoaded() override;

private:
    void *handle {nullptr};
    CreatePluginFunc create {nullptr};
    DestroyPluginFunc destroy {nullptr};
    std::shared_ptr<IPlugin> pluginPtr;
};
