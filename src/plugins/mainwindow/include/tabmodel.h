#pragma once
#include <iostream>
#include <QAbstractListModel>
#include <QtQmlIntegration/qqmlintegration.h>

#include "eventbus.h"

class TabsModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT

public:
    enum Roles { IdRole = Qt::UserRole + 1, TitleRole, UrlRole };

    TabsModel(std::weak_ptr<EventBus> bus, QObject* parent = nullptr)
        : QAbstractListModel(parent)
    {
        qDebug() << "TabsModel constructor";
        if (!bus.lock())
            return;

        bus.lock()->subscribe<AddUiTab>(this, [this](const AddUiTab& event) {
            beginResetModel();
            tabs_.push_back(event);
            endResetModel();
        });
    }

    int rowCount(const QModelIndex&) const override {
        return static_cast<int>(tabs_.size());
    }
    QVariant data(const QModelIndex& idx, int role) const override {
        const auto &[id, title, qmlUrl] = tabs_[idx.row()];
        switch (role) {
            case IdRole: return QString::fromStdString(id);
            case TitleRole: return QString::fromStdString(title);
            case UrlRole: return QString::fromStdString(qmlUrl);
            default: return {};
        }
    }

    QHash<int, QByteArray> roleNames() const override {
        static QHash<int, QByteArray> roles {
            {IdRole, "id"},
            {TitleRole, "title"},
            {UrlRole, "url"}
        };

        return roles;
    }

private:
    std::vector<AddUiTab> tabs_;
};
