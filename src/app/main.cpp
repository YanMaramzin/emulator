import core.logger.console;
import core.logger;
import core.pluginmanager;
import mainwindow;

int main()
{
    // Получаем UI плагин
    auto windowPlugin = pluginManager.get<MainWindow>("MainWindow");
    if (!windowPlugin) {
        return 0;
    }

    windowPlugin->show();

    pluginManager.shutdownAll();
    return 0;
}