#include <cassert>

#include <des/component/component.h>
#include <des/component/index.h>

struct data1 {};
struct data2 {};
struct data3 {};

int main()
{
    constexpr auto component1 = des::component::component<data1>;
    constexpr auto component2 = des::component::component<data2>;
    constexpr auto component3 = des::component::component<data3>;

    constexpr auto declaration = des::component::make_index(component1, component2, component3);

    auto index = declaration.make();
    assert(index.test(component1) == false);
    assert(index.test(component2) == false);
    assert(index.test(component3) == false);

    index.set(component1, 1);
    index.set(component2, 2);
    index.set(component3, 3);

    assert(index.get(component1) == 1);
    assert(index.get(component2) == 2);
    assert(index.get(component3) == 3);

    index.reset(component1);
    assert(index.test(component1) == false);
}
