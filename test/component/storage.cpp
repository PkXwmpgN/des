#include <iostream>
#include <cassert>
#include <des/context/config.h>
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

template<typename _Storage>
void test(const _Storage & storage)
{
    {
        constexpr auto config = des::context::make_config()
            .fixed_entity(des::meta::size_v<2>);

        constexpr auto eid1 = des::entity::make_entity_id(0);
        constexpr auto eid2 = des::entity::make_entity_id(1);

        auto fixed_storage = storage.make(config);

        fixed_storage.get(component1, eid1).x = 10;
        fixed_storage.get(component2, eid2).y = 10;

        assert(fixed_storage.get(component1, eid1).x == 10);
        assert(fixed_storage.get(component2, eid2).y == 10);
    }

    {
        constexpr auto config = des::context::make_config()
            .dynamic_entity(des::meta::size_v<2>);

        constexpr auto eid1 = des::entity::make_entity_id(0);
        constexpr auto eid2 = des::entity::make_entity_id(1);

        auto dynamic_storage = storage.make(config);

        dynamic_storage.get(component1, eid1).x = 10;
        dynamic_storage.get(component2, eid2).y = 10;

        assert(dynamic_storage.get(component1, eid1).x == 10);
        assert(dynamic_storage.get(component2, eid2).y == 10);
    }
}

int main()
{
    test(test_aos::storage);
    test(test_soa::storage);
}
