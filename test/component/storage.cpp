#include <iostream>
#include <cassert>
#include <des/context/config.h>
#include <des/component/component.h>
#include <des/component/buffer.h>
#include <des/component/storage.h>

struct data1
{
    float x;
};


struct data2
{
    int y;
};

// entity id dummy
struct ide
{
    ide(size_t i)
        : i_(i)
    {}

    size_t value() const { return i_;}

    size_t i_ = 0;
};

int main()
{
    constexpr auto component1 = des::component::component<data1>;
    constexpr auto component2 = des::component::component<data2>;

    constexpr auto buffer1 = des::component::make_buffer(component1);
    constexpr auto buffer2 = des::component::make_buffer(component2);

    constexpr auto fstorage = des::component::make_storage(buffer1, buffer2)
        .make(des::context::make_config(component1, component2));


    auto storage = std::decay_t<decltype(fstorage)>{};
    storage.get(component1, ide(1)).x = 10;
    storage.get(component2, ide(0)).y = 10;

    assert(storage.get(component1, ide(1)).x == 10);
    assert(storage.get(component2, ide(0)).y == 10);
}
