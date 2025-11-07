#pragma once

#include <QAbstractListModel>
#include <QString>
#include <QtQml/qqmlregistration.h>

#include "eventbus.h"


class PluginListModel : public QAbstractListModel {

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        LoadedRole
    };

    PluginListModel(std::weak_ptr<EventBus> bus,QObject *parent = nullptr) : QAbstractListModel(parent) {
        // bus.lock()->subscribe<>(this, [this](const auto &event) {

        // });
    };

    int rowCount(const QModelIndex &) const override {
        return m_plugins.size();
    };

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || index.row() >= m_plugins.size())
            return {};

        const auto &p = m_plugins[index.row()];
        switch (role) {
            case NameRole: return p.name;
            case LoadedRole: return p.loaded;
        }
        return {};
    };

    QHash<int, QByteArray> roleNames() const override {
        return {
                { NameRole, "name" },
                { LoadedRole, "loaded" }
        };
    }

private:
    struct PluginInfo {
        QString name;
        bool loaded;
    };

    QVector<PluginInfo> m_plugins;
    std::weak_ptr<EventBus> m_bus;
};
