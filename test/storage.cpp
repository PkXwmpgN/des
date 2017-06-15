#include <iostream>
#include <des/component/component.h>
#include <des/component/buffer.h>
#include <des/component/storage.h>

struct position
{
    float x;
    float y;
};


struct velocity
{
    float x;
    float y;
};


int main()
{
    constexpr auto c_position = des::component::component<position>;
    constexpr auto c_velocity = des::component::component<velocity>;

    constexpr auto cb_position = des::component::make_buffer(c_position);
    constexpr auto cb_velocity = des::component::make_buffer(c_velocity);

    constexpr auto fstorage = des::component::make_storage(cb_position, cb_velocity)
        .fixed(des::meta::size_v<1000>);
}
