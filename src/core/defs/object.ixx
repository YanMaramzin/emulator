module;
#include <memory>
#include <cassert>

export module core.object;

export class Object : public std::enable_shared_from_this<Object>
{
public:
    virtual ~Object() = default;

    std::shared_ptr<Object> self() noexcept {
        auto sp = weak_from_this().lock();
        assert(sp && "Object::self() called on a non-shared instance!");
        return sp;
    }

    std::shared_ptr<const Object> self() const noexcept {
        auto sp = weak_from_this().lock();
        assert(sp && "Object::self() called on a non-shared instance!");
        return sp;
    }
};
