#include <cassert>

#include <des/component/component.h>
#include <des/component/marker.h>

struct data1 {};
struct data2 {};
struct data3 {};

int main()
{
    constexpr auto component1 = des::component::component<data1>;
    constexpr auto component2 = des::component::component<data2>;
    constexpr auto component3 = des::component::component<data3>;

    {
        constexpr auto marker = des::component::make_marker(component1, component2, component3);
        static_assert(marker.size() == 3, "");
    }

    {
        auto marker = des::component::make_marker(component1, component2, component3);
        static_assert(marker.size() == 3, "");

        des::component::fill_marker(marker, component1, component3);
        assert(marker.test(component1) == true);
        assert(marker.test(component2) == false);
        assert(marker.test(component3) == true);

        marker.reset(component1);
        assert(marker.test(component1) == false);
    }
}
