#pragma once
#include <algorithm>
#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <typeindex>

struct AddUiTab {
    std::string id;           // уникальный ID вкладки
    std::string title;        // заголовок
    std::string qmlUrl;       // путь до QML-файла
};

class EventBus {
public:
     template<typename Event>
     using Handler = std::function<void(const Event&)>;

     template<typename Event, typename T>
     void subscribe(std::weak_ptr<T> owner, Handler<Event> handler) {
         std::scoped_lock lock(m_mutex);
         std::cout << "SUBSCRIBE" << std::endl;
         auto &vec = m_handlers[std::type_index(typeid(Event))];

         vec.emplace_back([owner, handler](const std::any &event) {
             // if (auto ptr = owner.lock())
                 handler(std::any_cast<const Event>(event));
         }, owner);
     }

     template<typename Event, typename T>
     void unsubscribe(std::weak_ptr<T> owner) {
         std::scoped_lock lock(m_mutex);
         auto it = m_handlers.find(std::type_index(typeid(Event)));
         if (it == m_handlers.end())
             return;

        auto &vec = it->second;
        vec.erase(
            std::remove_if(vec.begin(), vec.end(),
                           [&owner](const HandlerRecord &hr) {
                               auto locked_owner = owner.lock();
                               auto hr_locked = hr.owner.lock();
                               return locked_owner && hr_locked && hr_locked == locked_owner;
                           }),
            vec.end()
        );
    }

     template<typename Event, typename T>
     void subscribe(T *listener, std::function<void(const Event &)> handler) {
         subscribe<Event>(std::weak_ptr<T>(), std::move(handler));
     }


    template<typename Event>
    void publish(const Event &event) {
        std::scoped_lock lock(m_mutex);
        std::cout << "PUBLISH" << std::endl;
        auto find = m_handlers.find(std::type_index(typeid(Event)));
        if (find == m_handlers.end())
            return;

        auto &vec = find->second;

         for (const auto &[func, owner] : vec) {
             func(event);
         }

         // Потом очищаем "мертвые" обработчики
         vec.erase(
             std::remove_if(vec.begin(), vec.end(),
                            [](const HandlerRecord& hr) {
                                return hr.owner.expired();
                            }),
             vec.end()
         );
    }

private:
    struct HandlerRecord {
        std::function<void(const std::any&)> func;
        std::weak_ptr<void> owner;
    };

    std::unordered_map<std::type_index, std::vector<HandlerRecord>> m_handlers;
    std::mutex m_mutex;
};
