#include <utility>
#include <des/system/system.h>

struct process {};

int main()
{
    using system_type = std::decay_t<decltype(des::system::system<process>)>;

    static_assert(des::system::is_system<system_type>, "");
    static_assert(!des::system::is_system<process>, "");

    static_assert(std::is_same<process, system_type::underlying_type>::value, "");
}
