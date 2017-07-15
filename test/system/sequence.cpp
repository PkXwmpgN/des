#include <utility>
#include <des/component/component.h>
#include <des/system/system.h>
#include <des/system/node.h>

struct data1 {};
struct data2 {};
struct data3 {};

struct process1 {};
struct process2 {};
struct process3 {};

constexpr auto component1 = des::component::component<data1>;
constexpr auto component2 = des::component::component<data2>;
constexpr auto component3 = des::component::component<data3>;

constexpr auto system1 = des::system::system<process1>;
constexpr auto system2 = des::system::system<process2>;
constexpr auto system3 = des::system::system<process3>;

constexpr auto node1 = des::system::make_node(system1)
    .output(component1);

constexpr auto node2 = des::system::make_node(system2)
    .input(component1)
    .output(component2)
    .dependencies(node1);

constexpr auto node3 = des::system::make_node(system3)
    .input(component1, component2)
    .output(component3)
    .dependencies(node2);

template<typename _Sequence>
constexpr void test(_Sequence &&)
{
    using type = std::decay_t<_Sequence>;
    using type1 = std::tuple
    <
        std::decay_t<decltype(node1)>,
        std::decay_t<decltype(node2)>,
        std::decay_t<decltype(node3)>
    >;

    static_assert(std::tuple_size<type>::value == 3, "");
    static_assert(std::is_same<type1, type>::value, "");
}

int main()
{
    test(des::system::make_sequence(node1, node2, node3));
    test(des::system::make_sequence(node1, node3, node2));
    test(des::system::make_sequence(node2, node1, node3));
    test(des::system::make_sequence(node2, node3, node1));
    test(des::system::make_sequence(node3, node1, node2));
    test(des::system::make_sequence(node3, node2, node1));
}
