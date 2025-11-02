#pragma once

class IPlugin
{
public:
    virtual ~IPlugin() = default;
    virtual void initialize() = 0;
    virtual void shutdown() = 0;
};
