#pragma once

#include <iostream>
#include <memory> // for std::unique_ptr
#include <concepts> // for std::derived_from
#include <cstdint> // for std::int32_t

namespace heap
{
/// This is a base class that gets used for diagnostical purposes.
struct Diagnostics
{
    static inline std::int32_t allocated_count {0};
    static inline std::int32_t allocated_bytes {0};
};

/// Call destructor (unless nullptr) and then deallocate().
/// Direct usage is not recommended; use smart pointers instead.
template <typename T>
void destroy(T* const obj)
{
    if (obj != nullptr)
    {
        obj->~T();
    }
    delete(obj);
}

/// This is a non-op helper wrapper over destroy() needed for delayed function template instantiation.
struct Destroyer final
{
    template <typename T>
    void operator()(T* const obj)
    {
        destroy(obj);
    }
};

/// Simple unique pointer that automatically calls destroy().
template <typename T>
class UniquePtr final: public std::unique_ptr<T, Destroyer>, public Diagnostics
{
    using P = std::unique_ptr<T, Destroyer>;

public:
    UniquePtr() noexcept : P(nullptr, {})
    {
        std::cout << "UniquePtr Constructor 1" << std::endl;
        increaseDiag();
    }

    explicit UniquePtr(T* const p) noexcept : P(p, {}) // explicit: Not used for implicit conversions
    {
        std::cout << "UniquePtr Constructor 2" << std::endl;
        increaseDiag();
    }

    UniquePtr(std::nullptr_t) noexcept : P(nullptr) // Destroyer is not passed, since nothing to destroy (nothing is owned)
    {
        std::cout << "UniquePtr Constructor 3" << std::endl;
        increaseDiag();
    }

    template <std::derived_from<T> U> // The following constructor can only be called if U is derived from T
    // This will call constructor #2 to instantiate the unique_ptr (of derived class type)
    UniquePtr(UniquePtr<U>&& other) noexcept : UniquePtr(other.release())
    {
        std::cout << "UniquePtr Constructor 4" << std::endl;
    }

    UniquePtr(UniquePtr&&) noexcept = default; // Move CTOR
    UniquePtr& operator=(UniquePtr&&) noexcept = default; // Move assignment operator

    ~UniquePtr() noexcept // Destructor
    {
        std::cout << "UniquePtr Destructor" << std::endl;
        decreaseDiag();
    }

    UniquePtr(const UniquePtr&) = delete; // Copy constructor
    UniquePtr& operator=(const UniquePtr&) = delete; // Assignment operator

    static void increaseDiag()
    {
        allocated_count++;
        auto size_type = sizeof(T);
        allocated_bytes += static_cast<std::int32_t>(size_type);
    }

    static void decreaseDiag()
    {
        allocated_count--;
        auto size_type = sizeof(T);
        allocated_bytes -= static_cast<std::int32_t>(size_type);
    }
};

/// Simple object construction helper that allocates memory and calls placement new on it with the specified args.
/// Returns unique pointer which is nullptr if OOM.
template <typename T, typename...CtorArgs>
[[nodiscard]] UniquePtr<T> makeUnique(CtorArgs&&... args)
{
    if (void* const mem = malloc(sizeof(T)))
    {
        return UniquePtr<T>(new (mem) T(std::forward<CtorArgs>(args)...));
    }
    return UniquePtr<T>();
}
}
