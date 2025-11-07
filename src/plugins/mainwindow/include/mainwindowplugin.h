#pragma once
#include <iplugin.h>
#include <qmluihost.h>

#include "tabmodel.h"

class MainWindowPlugin : public IPlugin, public std::enable_shared_from_this<MainWindowPlugin>
{
public:
    void shutdown() override {

    };

    void initialize(PluginContext &ctx) override {

        m_uihost = std::make_shared<QmlUiHost>();
        ctx.uihost = m_uihost;

        qmlRegisterSingletonType<TabsModel>(
            "CoreModels", 1, 0, "TabsModel",
            [&ctx](QQmlEngine *, QJSEngine *) -> QObject * {
                return new TabsModel(ctx.bus);
            });

        m_uihost->loadQml("qrc:/qml/MainWindow.qml");
    };

private:
    std::shared_ptr<QmlUiHost> m_uihost;
};

extern "C" IPlugin *createPlugin() { return new MainWindowPlugin(); }

extern "C" void destroyPlugin(IPlugin *plugin) { delete plugin; };