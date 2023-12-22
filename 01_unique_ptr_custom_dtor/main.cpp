#include "heap_unique.hpp"

// std::int32_t heap::Diagnostics::allocated_count = 0;
// std::int32_t heap::Diagnostics::allocated_bytes = 0;

struct Foo // object to manage
{
    Foo() { std::cout << "Foo ctor\n"; }
    Foo(const Foo&) { std::cout << "Foo copy ctor\n"; }
    Foo(Foo&&) { std::cout << "Foo move ctor\n"; }
    ~Foo() { std::cout << "~Foo dtor\n"; }
};

class Base
{
public:
    Base() { std::cout << "Base ctor" << std::endl; }
    virtual ~Base() { std::cout << "~Base dtor" << std::endl; } // Has to be virtual, otherwise Derived destructor won't be called.
};

class Derived : public Base
{
public:
    Derived() { std::cout << "Derived ctor" << std::endl; }
    virtual ~Derived() { std::cout << "~Derived dtor" << std::endl; }
};

int main()
{
    // makeUnique
    std::cout << "=== TEST: makeUnique ===" << std::endl;
    {
        heap::UniquePtr<Foo> foo = heap::makeUnique<Foo>();
        std::cout << "allocated_count: " << heap::Diagnostics::allocated_count << std::endl;
        std::cout << "allocated_bytes: " << heap::Diagnostics::allocated_bytes << std::endl;
    }
    std::cout << "allocated_count: " << heap::Diagnostics::allocated_count << std::endl;
    std::cout << "allocated_bytes: " << heap::Diagnostics::allocated_bytes << std::endl;

    // UniquePtr Constructor 1
    std::cout << "=== TEST: Contructor 1 ===" << std::endl;
    {
        heap::UniquePtr<Foo> heap_var;
        std::cout << "allocated_count: " << heap::Diagnostics::allocated_count << std::endl;
        std::cout << "allocated_bytes: " << heap::Diagnostics::allocated_bytes << std::endl;
    }
    std::cout << "allocated_count: " << heap::Diagnostics::allocated_count << std::endl;
    std::cout << "allocated_bytes: " << heap::Diagnostics::allocated_bytes << std::endl;

    // UniquePtr Constructor 2
    std::cout << "=== TEST: Contructor 2 ===" << std::endl;
    {
        Foo* foo_ptr = new Foo();
        heap::UniquePtr<Foo> foo_unique(foo_ptr); // Now UniquePtr is responsible for managing the lifetime.
        std::cout << "allocated_count: " << heap::Diagnostics::allocated_count << std::endl;
        std::cout << "allocated_bytes: " << heap::Diagnostics::allocated_bytes << std::endl;
    }
    std::cout << "allocated_count: " << heap::Diagnostics::allocated_count << std::endl;
    std::cout << "allocated_bytes: " << heap::Diagnostics::allocated_bytes << std::endl;

    // UniquePtr Constructor 3
    std::cout << "=== TEST: Contructor 3 ===" << std::endl;
    {
        heap::UniquePtr<Foo> foo_null_ptr(nullptr);
        std::cout << "allocated_count: " << heap::Diagnostics::allocated_count << std::endl;
        std::cout << "allocated_bytes: " << heap::Diagnostics::allocated_bytes << std::endl;
        foo_null_ptr = heap::makeUnique<Foo>(); // Move assignment operator
    }
    std::cout << "allocated_count: " << heap::Diagnostics::allocated_count << std::endl;
    std::cout << "allocated_bytes: " << heap::Diagnostics::allocated_bytes << std::endl;

    // UniquePtr Constructor 4
    std::cout << "=== TEST: Contructor 4 ===" << std::endl;
    {
        heap::UniquePtr<Derived> derived_ptr(new Derived());
        heap::UniquePtr<Base> base_ptr(std::move(derived_ptr));
        std::cout << "allocated_count: " << heap::Diagnostics::allocated_count << std::endl;
        std::cout << "allocated_bytes: " << heap::Diagnostics::allocated_bytes << std::endl;
    }
    std::cout << "allocated_count: " << heap::Diagnostics::allocated_count << std::endl;
    std::cout << "allocated_bytes: " << heap::Diagnostics::allocated_bytes << std::endl;
}
