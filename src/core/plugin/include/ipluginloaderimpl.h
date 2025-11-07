#pragma once
#include <memory>
#include <iplugin.h>

class IPluginLoaderImpl
{
public:
    virtual ~IPluginLoaderImpl() = default;

    virtual std::shared_ptr<IPlugin> load(const std::string &path) = 0;
    virtual void unload() = 0;
    virtual bool isLoaded() = 0;
};
