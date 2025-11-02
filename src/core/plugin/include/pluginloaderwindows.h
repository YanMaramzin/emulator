// #pragma once
//
// #include "ipluginloaderimpl.h"
// #include <windows.h>
// #include <iostream>
//
// using CreatePluginFunc = IPlugin* (*)();
// using DestroyPluginFunc = void (*)(IPlugin*);
//
// class PluginLoaderWindows final : public IPluginLoaderImpl {
// public:
//     ~PluginLoaderWindows() { unload(); }
//
//     std::shared_ptr<IPlugin> load(const std::string& path) override {
//         if (handle) unload();
//
//         handle = LoadLibraryA(path.c_str());
//         if (!handle) {
//             std::cerr << "LoadLibrary failed: " << GetLastError() << "\n";
//             return nullptr;
//         }
//
//         create = reinterpret_cast<CreatePluginFunc>(GetProcAddress(handle, "createPlugin"));
//         destroy = reinterpret_cast<DestroyPluginFunc>(GetProcAddress(handle, "destroyPlugin"));
//
//         if (!create || !destroy) {
//             std::cerr << "Plugin missing create/destroy functions\n";
//             unload();
//             return nullptr;
//         }
//
//         IPlugin* plugin = create();
//         pluginPtr = std::shared_ptr<IPlugin>(plugin, [this](IPlugin* p){ destroy(p); });
//         return pluginPtr;
//     }
//
//     void unload() override {
//         pluginPtr.reset();
//         if (handle) {
//             FreeLibrary(handle);
//             handle = nullptr;
//         }
//     }
//
//     bool isLoaded() const override {
//         return handle != nullptr;
//     }
//
// private:
//     HMODULE handle = nullptr;
//     std::shared_ptr<IPlugin> pluginPtr;
//     CreatePluginFunc create = nullptr;
//     DestroyPluginFunc destroy = nullptr;
// };
