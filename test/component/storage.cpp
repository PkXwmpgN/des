#include <iostream>
#include <cassert>
#include <des/data/config.h>
#include <des/component/component.h>
#include <des/component/buffer.h>
#include <des/component/storage.h>
#include <des/entity/entity.h>

struct data1
{
    float x;
};

struct data2
{
    int y;
};

constexpr auto component1 = des::component::component<data1>;
constexpr auto component2 = des::component::component<data2>;

// struct-of-array
namespace test_soa
{
    constexpr auto buffer1 = des::component::make_buffer(component1);
    constexpr auto buffer2 = des::component::make_buffer(component2);

    constexpr auto storage = des::component::make_storage(buffer1, buffer2);
}

// array-of-struct
namespace test_aos
{
    constexpr auto buffer = des::component::make_buffer(component1, component2);
    constexpr auto storage = des::component::make_storage(buffer);
}

namespace fixed
{
    constexpr auto config = des::data::make_config()
        .fixed_entity(des::meta::size_v<2>);
}

namespace dynamic
{
    constexpr auto config = des::data::make_config()
        .dynamic_entity(des::meta::size_v<2>);
}

template<typename _Storage>
void start_test(const _Storage & storage)
{
    test(storage.make(fixed::config));
    test(storage.make(dynamic::config));
}

template<typename _Storage>
void test(_Storage && storage)
{
    auto index1 = storage.add(component1);
    auto index2 = storage.add(component1);
    auto index3 = storage.add(component2);

    assert(storage.size(component1) == 2);
    assert(storage.size(component2) == 1);

    storage.get(component1, index1).x = 0;
    storage.get(component1, index2).x = 1;
    storage.get(component2, index3).y = 1;

    assert(storage.get(component1, index1).x == 0);
    assert(storage.get(component1, index2).x == 1);
    assert(storage.get(component2, index3).y == 1);
}

int main()
{
    start_test(test_aos::storage);
    start_test(test_soa::storage);
}
