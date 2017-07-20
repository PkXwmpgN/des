#include <cassert>

#include <des/component/component.h>
#include <des/component/buffer.h>
#include <des/component/storage.h>
#include <des/entity/buffer.h>
#include <des/entity/storage.h>
#include <des/data/service.h>
#include <des/data/storage.h>
#include <des/data/config.h>

struct data1
{
    int x;
};
struct data2
{
    int y;
};
struct data3
{
    int z;
};

constexpr auto component1 = des::component::component<data1>;
constexpr auto component2 = des::component::component<data2>;
constexpr auto component3 = des::component::component<data3>;

constexpr auto make_component_storage()
{
    constexpr auto buffer1 = des::component::make_buffer(component1);
    constexpr auto buffer2 = des::component::make_buffer(component2);
    constexpr auto buffer3 = des::component::make_buffer(component3);
    return des::component::make_storage(buffer1, buffer2, buffer3);
}

constexpr auto make_entity_storage()
{
    constexpr auto index = make_component_storage().index();
    constexpr auto buffer = des::entity::make_buffer(index);
    return des::entity::make_storage(buffer);
}

constexpr auto make_data_service()
{
    constexpr auto component_storage = make_component_storage();
    constexpr auto entity_storage = make_entity_storage();

    constexpr auto storage = des::data::make_storage()
        .components(component_storage)
        .entities(entity_storage);

    return des::data::make_service(storage);
}

namespace fixed
{
    constexpr auto config = des::data::make_config()
        .fixed_entity(des::meta::size_v<3>);
}

namespace dynamic
{
    constexpr auto config = des::data::make_config()
        .dynamic_entity(des::meta::size_v<2>);
}

template<typename _Config>
void test(const _Config & config)
{
    constexpr auto service = make_data_service();
    auto data = service.make(config);

    auto ide1 = data.create_entity();
    data.add_component(component1, ide1).x = 1;
    data.add_component(component2, ide1).y = 2;
    data.add_component(component3, ide1).z = 3;

    assert(data.test_component(component1, ide1));
    assert(data.test_component(component2, ide1));
    assert(data.test_component(component3, ide1));
    assert(data.get_component(component1, ide1).x == 1);
    assert(data.get_component(component2, ide1).y == 2);
    assert(data.get_component(component3, ide1).z == 3);

    auto ide2 = data.create_entity();
    decltype(auto) ref_comp1 = data.add_component(component1, ide2);
    decltype(auto) ref_comp2 = data.add_component(component1, ide2);
    assert(&ref_comp1 == &ref_comp2);
    ref_comp1.x = 5;

    assert(data.test_component(component1, ide2));
    assert(!data.test_component(component2, ide2));
    assert(!data.test_component(component3, ide2));

    data.remove_component(component1, ide1);
    assert(data.test_component(component1, ide1) == false);
    assert(data.test_component(component1, ide2) == true);
    assert(data.get_component(component1, ide2).x == 5);
}

int main()
{
    test(fixed::config);
    test(dynamic::config);
}
