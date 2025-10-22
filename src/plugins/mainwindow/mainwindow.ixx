module;
#include <iostream>
#include <memory>
#include <string>
#include <compare>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

export module mainwindow;

import core.iplugin;

export class MainWindow : public IPlugin {
public:
    ~MainWindow() override = default;
    void initialize() override {
        std::cout << "MainWindow initialized\n";

        // int argc = 0;
        // char** argv = nullptr;
        // app_ = std::make_unique<QGuiApplication>(argc, argv);
        // engine_ = std::make_unique<QQmlApplicationEngine>();
        //
        // const QUrl url(u"qrc:/qml/MainWindow.qml"_qs);
        // QObject::connect(
        //     engine_.get(), &QQmlApplicationEngine::objectCreated,
        //     app_.get(), [url](QObject *obj, const QUrl &objUrl) {
        //         if (!obj && url == objUrl)
        //             QCoreApplication::exit(-1);
        //     },
        //     Qt::QueuedConnection);
        //
        // engine_->load(url);
        // open_ = true;
        int argc = 0;
        char** argv = nullptr;
        app_ = std::make_unique<QGuiApplication>(argc, argv);
        // engine_ = std::make_unique<QQmlApplicationEngine>();
        engine_.load("qrc:/mainwindow/qml/MainWindow.qml");
        // open_ = true;

        // Запуск Qt event loop в отдельном потоке
    };
    void shutdown() override {
        std::cout << "MainWindow shutdown\n";
    };
    const PluginMetadata metadata() const override {
        static PluginMetadata meta{
            "MainWindow", "MainWindow", "1.0", "Me",
            "Provides QML-based UI window", "1.0"
        };
        return meta;
    };

    void show() {
        if (!app_)
            return;
        std::cout << "[UI] Executing Qt event loop...\n";
        app_->exec();
    }

private:
    std::unique_ptr<QGuiApplication> app_;
    QQmlApplicationEngine engine_;
    // bool open_ = false;
};

extern "C" IPlugin* createPlugin() { return new MainWindow(); }