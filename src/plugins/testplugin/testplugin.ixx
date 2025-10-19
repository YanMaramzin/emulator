module;
#include <iostream>
#include <memory>

export module testplugin;

import core.iplugin;
import core.events;

class TestPlugin final : public IPlugin {
public:
    ~TestPlugin() override = default;
    void initialize() override {
        std::cout << "TestPlugin initialized\n";

        // Подписка на MyEvent через EventSystem
        if (const auto bus = eventSystem()) {
            bus->subscribe<MyEvent>(self(),
                [this](const MyEvent &e) {
                    std::cout << "Received MyEvent: " << e.value << "\n";
                });
        }
    }

    void shutdown() override {
        std::cout << "TestPlugin shutdown\n";
        if (const auto bus = eventSystem()) {
            // Отписка всех колбеков текущего объекта
            bus->unsubscribeAll(self());
        }
    }

    const PluginMetadata metadata() const override {
        static PluginMetadata meta{
            "testplugin",
            "Test Plugin",
            "1.0",
            "Author",
            "A test plugin",
            "1.0"
        };
        return meta;
    }
};

// Фабричная функция — именно её вызовет PluginLoader
extern "C" IPlugin *createPlugin() {
    return new TestPlugin();
}

// // Функция для корректного удаления
// extern "C" void destroy_plugin(IPlugin* plugin) {
//     delete plugin;
// }