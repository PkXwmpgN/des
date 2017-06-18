#include <utility>
#include <des/component/component.h>

struct data {};

int main()
{
    using test = std::decay_t<decltype(des::component::component<data>)>;

    static_assert(des::component::is_component<test>, "");
    static_assert(!des::component::is_component<data>, "");

    static_assert(std::is_same<data, test::underlying_type>::value, "");
}
