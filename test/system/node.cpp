#include <utility>
#include <des/component/component.h>
#include <des/system/system.h>
#include <des/system/node.h>

struct data1 {};
struct data2 {};
struct data3 {};

struct process1 {};
struct process2 {};

int main()
{
    constexpr auto component1 = des::component::component<data1>;
    constexpr auto component2 = des::component::component<data2>;
    constexpr auto component3 = des::component::component<data3>;

    constexpr auto system1 = des::system::system<process1>;
    constexpr auto system2 = des::system::system<process2>;

    constexpr auto node1 = des::system::make_node(system1)
        .output(component1);

    constexpr auto node2 = des::system::make_node(system2)
        .input(component1)
        .output(component2, component3)
        .dependencies(system1);

    (void)node1;
    (void)node2;
}
