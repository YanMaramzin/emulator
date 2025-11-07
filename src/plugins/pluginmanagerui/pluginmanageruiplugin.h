#pragma once
#include <iostream>
#include <QtQml/qqml.h>
#include "pluginmodel.h"

#include "iplugin.h"
#include "qmluihost.h"

class PluginManagerUiPlugin : public IPlugin, public std::enable_shared_from_this<PluginManagerUiPlugin> {
public:
    void initialize(PluginContext &ctx) override {

        if (!ctx.uihost.lock()) {
            std::cout << "НЕТ UI!";
            return;
        }

        const auto cast = std::dynamic_pointer_cast<QmlUiHost>(ctx.uihost.lock());

        qmlRegisterSingletonType<PluginListModel>(
            "CoreModels", 1, 0, "PluginListModel",
            [ctx](QQmlEngine *, QJSEngine *) -> QObject * {
                return new PluginListModel(ctx.bus);
            });

        ctx.bus->publish(AddUiTab{
            .id = "plugin_manager",
            .title = "PluginManager",
            .qmlUrl = "qrc:/qml/PluginManager.qml"
        });
    }

    void shutdown() override {

    }
};

extern "C" IPlugin *createPlugin() { return new PluginManagerUiPlugin(); }

extern "C" void destroyPlugin(IPlugin *plugin) { delete plugin; }

