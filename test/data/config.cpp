#include <utility>
#include <tuple>

#include <des/data/config.h>

int main()
{
    {
        constexpr auto config = des::data::make_config();

        static_assert(config.fixed() == true, "");
        static_assert(config.capacity() == 1024, "");
    }

    {
        constexpr auto config = des::data::make_config()
            .fixed_entity(des::meta::sz_v<10>);

        static_assert(config.fixed() == true, "");
        static_assert(config.capacity() == 10, "");
    }

    {
        constexpr auto config = des::data::make_config()
            .dynamic_entity(des::meta::sz_v<100>);

        static_assert(config.fixed() == false, "");
        static_assert(config.capacity() == 100, "");
    }
}
