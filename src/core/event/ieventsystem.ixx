module;
#include <memory>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <algorithm>
#include <iostream>

export module core.ieventsystem;
import core.object;
import core.events;

export class IEventSystem {
public:
    virtual ~IEventSystem() = default;

    // Подписка на событие типа Event
    template<typename Event>
    void subscribe(std::shared_ptr<Object> obj, std::function<void(const Event&)> callback) {
        auto &vec = listeners_[std::type_index(typeid(Event))];
        vec.push_back({obj, [cb = std::move(callback)](const void* e) {
            cb(*static_cast<const Event*>(e));
        }});
    }

    // Отписка всех колбеков объекта
    void unsubscribeAll(std::shared_ptr<Object> obj) {
        for (auto &pair : listeners_) {
            auto &vec = pair.second;
            vec.erase(std::remove_if(vec.begin(), vec.end(),
                        [&](const ListenerEntry &entry) { return entry.obj.lock() == obj; }),
                      vec.end());
        }
    }

    // Публикация события
    template<typename Event>
    void publish(const Event &e) {
        // const auto tmp = std::type_index(typeid(Event));
        // std::cout << tmp.name() << " " << tmp.hash_code() << std::endl;
        // std::cout << listeners_.begin()->first.name() << " " << listeners_.begin()->first.hash_code() << std::endl;
        const auto it = listeners_.find(std::type_index(typeid(Event)));
        if (it == listeners_.end())
            return;

        for (auto &[obj, callback] : it->second) {
            if (auto objPtr = obj.lock())
                callback(&e);
        }
    }

private:
    struct ListenerEntry {
        std::weak_ptr<Object> obj;
        std::function<void(const void*)> callback;
    };

    std::unordered_map<std::type_index, std::vector<ListenerEntry>> listeners_;
};
