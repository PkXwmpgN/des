#include <iostream>
#include <des/component/component.h>
#include <des/component/buffer.h>
#include <des/component/storage.h>

struct data1
{
    float x;
};


struct data2
{
    int x;
};


int main()
{
    constexpr auto component1 = des::component::component<data1>;
    constexpr auto component2 = des::component::component<data2>;

    constexpr auto buffer1 = des::component::make_buffer(component1);
    constexpr auto buffer2 = des::component::make_buffer(component2);

    constexpr auto fstorage = des::component::make_storage(buffer1, buffer2)
        .fixed(des::meta::size_v<1000>);
    (void)fstorage;
}
