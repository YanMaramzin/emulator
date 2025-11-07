#pragma once

#include "iuihost.h"
#include <QDebug>
#include <QQmlApplicationEngine>

class QmlUiHost : public IUiHost {
public:

    void addPanel(const std::string& id, const std::string& resource) override {
        // В реальности ты можешь добавить компонент в StackView, TabView и т.п.
        qDebug() << "Add QML panel:" << QString::fromStdString(id)
                 << "=>" << QString::fromStdString(resource);
        m_engine.load(QUrl(QString::fromStdString(resource)));
    }

    void removePanel(const std::string& id) override {
        qDebug() << "Remove panel:" << QString::fromStdString(id);
    }

    void showMessage(const std::string& message) override {
        qDebug() << "UI message:" << QString::fromStdString(message);
    }

    void loadQml(const std::string& path) {
        m_engine.load(QString::fromStdString(path));

        if (m_engine.rootObjects().isEmpty())
            qCritical() << "QML UI not loaded:" << QString::fromStdString(path);
    }

private:
    QQmlApplicationEngine m_engine;
};
