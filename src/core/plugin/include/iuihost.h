#pragma once
#include <string>
#include <functional>

class IUiHost {
public:
    virtual ~IUiHost() = default;

    // Добавить QML или Widget панель
    virtual void addPanel(const std::string& id, const std::string& resource) = 0;

    // Удалить панель (по желанию)
    virtual void removePanel(const std::string& id) = 0;

    // Показать уведомление / статус (универсальный API)
    virtual void showMessage(const std::string& message) = 0;
};
