#include <utility>
#include <tuple>

#include <des/component/component.h>
#include <des/context/config.h>

struct data1 {};
struct data2 {};

int main()
{
    constexpr auto component1 = des::component::component<data1>;
    constexpr auto component2 = des::component::component<data2>;

    {
        constexpr auto config = des::context::make_config(component1, component2);

        using list = std::decay_t<decltype(config.components())>;
        static_assert(std::is_same<std::tuple_element_t<0, list>,
                                   std::decay_t<decltype(component1)>>::value, "");
        static_assert(std::is_same<std::tuple_element_t<1, list>,
                                   std::decay_t<decltype(component2)>>::value, "");

        static_assert(config.fixed() == true, "");
        static_assert(config.capacity() == 1024, "");
    }

    {
        constexpr auto config = des::context::make_config(component1, component2)
            .fixed_entity(des::meta::size_v<10>);

        using list = std::decay_t<decltype(config.components())>;
        static_assert(std::is_same<std::tuple_element_t<0, list>,
                                   std::decay_t<decltype(component1)>>::value, "");
        static_assert(std::is_same<std::tuple_element_t<1, list>,
                                   std::decay_t<decltype(component2)>>::value, "");

        static_assert(config.fixed() == true, "");
        static_assert(config.capacity() == 10, "");
    }

    {
        constexpr auto config = des::context::make_config(component1, component2)
            .dynamic_entity(des::meta::size_v<100>);

        using list = std::decay_t<decltype(config.components())>;
        static_assert(std::is_same<std::tuple_element_t<0, list>,
                                   std::decay_t<decltype(component1)>>::value, "");
        static_assert(std::is_same<std::tuple_element_t<1, list>,
                                   std::decay_t<decltype(component2)>>::value, "");

        static_assert(config.fixed() == false, "");
        static_assert(config.capacity() == 100, "");
    }
}
