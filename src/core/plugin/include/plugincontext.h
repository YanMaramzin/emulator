#pragma once
#include <eventbus.h>
#include <iuihost.h>

struct PluginContext {
    std::shared_ptr<EventBus> bus;
    std::weak_ptr<IUiHost> uihost;
};
