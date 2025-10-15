module;
#include <cstdio>
#include <string>

export module testplugin;

import core.iplugin;

export class TestPlugin : public IPlugin {
public:
    void initialize() override {
        printf("TestPlugin initialized!\n");
    }

    void shutdown() override {
        printf("TestPlugin shutdown!\n");
    }

    std::string name() const override {
        return "TestPlugin";
    }
};

// Фабричная функция — именно её вызовет PluginLoader
extern "C" IPlugin* createPlugin() {
    return new TestPlugin();
}

// // Функция для корректного удаления
// extern "C" void destroy_plugin(IPlugin* plugin) {
//     delete plugin;
// }