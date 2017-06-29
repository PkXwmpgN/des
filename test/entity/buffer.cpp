#include <cassert>

#include <des/component/component.h>
#include <des/context/marker.h>
#include <des/context/config.h>
#include <des/entity/entity.h>
#include <des/entity/buffer.h>

struct data1 {};
struct data2 {};
struct data3 {};

int main()
{
    constexpr auto component1 = des::component::component<data1>;
    constexpr auto component2 = des::component::component<data2>;
    constexpr auto component3 = des::component::component<data3>;

    constexpr auto marker = des::context::make_marker(component1, component2, component3);
    constexpr auto config = des::context::make_config();

    {
        constexpr auto buffer = des::entity::make_buffer(marker);
        (void)buffer;
    }

    {
        constexpr auto eid1 = des::entity::make_entity_id(0);
        constexpr auto eid2 = des::entity::make_entity_id(1);

        auto buffer = des::entity::make_buffer(marker)
            .make(config);
        buffer.get(eid1).register_component(component1);
        buffer.get(eid1).register_component(component3);

        assert(buffer.get(eid1).test_component(component1));
        assert(buffer.get(eid1).test_component(component3));
        assert(!buffer.get(eid1).test_component(component2));
        assert(!buffer.get(eid2).test_component(component1));
        assert(!buffer.get(eid2).test_component(component3));
        assert(!buffer.get(eid2).test_component(component2));
    }
}
