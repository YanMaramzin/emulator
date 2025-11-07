#include <pluginmanager.h>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    PluginManager manager;

    manager.loadPluginsFromFolder("../../bin/plugins");
    manager.initializeAll();
    return app.exec();
}
