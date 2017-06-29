#include <utility>
#include <tuple>

#include <des/context/config.h>

int main()
{
    {
        constexpr auto config = des::context::make_config();

        static_assert(config.fixed() == true, "");
        static_assert(config.capacity() == 1024, "");
    }

    {
        constexpr auto config = des::context::make_config()
            .fixed_entity(des::meta::size_v<10>);

        static_assert(config.fixed() == true, "");
        static_assert(config.capacity() == 10, "");
    }

    {
        constexpr auto config = des::context::make_config()
            .dynamic_entity(des::meta::size_v<100>);

        static_assert(config.fixed() == false, "");
        static_assert(config.capacity() == 100, "");
    }
}
