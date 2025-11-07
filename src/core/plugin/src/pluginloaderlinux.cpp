#include "pluginloaderlinux.h"
#include <dlfcn.h>
#include <iostream>

PluginLoaderLinux::~PluginLoaderLinux() {
    unload();
}

std::shared_ptr<IPlugin> PluginLoaderLinux::load(const std::string &path) {
    handle = dlopen(path.c_str(), RTLD_LAZY);

    if (!handle) {
        std::cerr << "dlopen failed" << dlerror() << std::endl;
        return nullptr;
    }

    create = reinterpret_cast<CreatePluginFunc>(dlsym(handle, "createPlugin"));
    destroy = reinterpret_cast<DestroyPluginFunc>(dlsym(handle, "destroyPlugin"));

    if (!create) {
        std::cerr << "Plugin missing create functions\n";
        unload();
        return nullptr;
    }

    if (!destroy) {
        std::cerr << "Plugin missing destroy functions\n";
        unload();
        return nullptr;
    }

    IPlugin *plugin = create();
    pluginPtr = std::shared_ptr<IPlugin>(plugin, [this](IPlugin* p){ destroy(p); });
    return pluginPtr;
}

void PluginLoaderLinux::unload() {
    if (handle) {
        dlclose(handle);
        handle = nullptr;
    }
}

bool PluginLoaderLinux::isLoaded() {
    return !handle;
}
