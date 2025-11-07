#pragma once
#include <plugincontext.h>

class IPlugin {
public:
    virtual ~IPlugin() = default;
    virtual void initialize(PluginContext &ctx) = 0;
    virtual void shutdown() = 0;
};
