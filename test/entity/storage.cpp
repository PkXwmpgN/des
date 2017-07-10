#include <cassert>

#include <des/component/component.h>
#include <des/component/buffer.h>
#include <des/component/storage.h>
#include <des/data/config.h>
#include <des/entity/buffer.h>
#include <des/entity/storage.h>

struct data1 {};
struct data2 {};
struct data3 {};

constexpr auto component1 = des::component::component<data1>;
constexpr auto component2 = des::component::component<data2>;
constexpr auto component3 = des::component::component<data3>;

namespace components
{
    constexpr auto buffer1 = des::component::make_buffer(component1);
    constexpr auto buffer2 = des::component::make_buffer(component2);
    constexpr auto buffer3 = des::component::make_buffer(component3);
    constexpr auto storage = des::component::make_storage(buffer1, buffer2, buffer3);
}

namespace entity
{
    constexpr auto index = components::storage.index();
    constexpr auto buffer = des::entity::make_buffer(index);
    constexpr auto storage = des::entity::make_storage(buffer);
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

template<typename _Config>
void test(const _Config & config)
{
    auto components = components::storage.make(config);
    auto entities = entity::storage.make(config);

    auto ide1 = entities.add();
    auto ide2 = entities.add();

    entities.get(ide1).register_component(component1, components);
    entities.get(ide1).register_component(component3, components);

    assert(entities.get(ide1).test_component(component1));
    assert(entities.get(ide1).test_component(component3));
    assert(!entities.get(ide1).test_component(component2));
    assert(!entities.get(ide2).test_component(component1));
    assert(!entities.get(ide2).test_component(component3));
    assert(!entities.get(ide2).test_component(component2));
}

int main()
{
    test(fixed::config);
    test(dynamic::config);
}
