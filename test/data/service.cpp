#include <cassert>

#include <des/component/component.h>
#include <des/component/buffer.h>
#include <des/component/storage.h>
#include <des/component/marker.h>
#include <des/entity/entity.h>
#include <des/entity/buffer.h>
#include <des/entity/storage.h>
#include <des/data/service.h>
#include <des/data/storage.h>
#include <des/data/config.h>

struct data1 {};
struct data2 {};
struct data3 {};

constexpr auto component1 = des::component::component<data1>;
constexpr auto component2 = des::component::component<data2>;
constexpr auto component3 = des::component::component<data3>;

constexpr auto marker = des::component::make_marker(component1, component2, component3);

constexpr auto make_component_storage()
{
    constexpr auto buffer1 = des::component::make_buffer(component1);
    constexpr auto buffer2 = des::component::make_buffer(component2);
    constexpr auto buffer3 = des::component::make_buffer(component3);
    return des::component::make_storage(buffer1, buffer2, buffer3);
}

constexpr auto make_entity_storage()
{
    constexpr auto buffer = des::entity::make_buffer(marker);
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
    constexpr auto service = make_data_service();
    auto data = service.make(config);
    (void)data;
}

int main()
{
    test(fixed::config);
    test(dynamic::config);
}
