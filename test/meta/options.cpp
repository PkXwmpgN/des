#include <tuple>
#include <type_traits>
#include <des/meta/types.h>
#include <des/meta/options.h>

struct A {};
struct B {};
struct C {};

namespace key
{
    constexpr auto test1 = des::meta::options::key_v<0>;
    constexpr auto test2 = des::meta::options::key_v<1>;
    constexpr auto test3 = des::meta::options::key_v<2>;
}

int main()
{
    auto opt1 = des::meta::options::set(des::meta::options::empty_v, key::test1, A{});
    auto opt2 = des::meta::options::set(opt1, key::test2, B{});
    auto opt3 = des::meta::options::set(opt2, key::test3, C{});

    static_assert(des::meta::options::size(opt1) == 1, "");
    static_assert(des::meta::options::size(opt2) == 2, "");
    static_assert(des::meta::options::size(opt3) == 3, "");

    static_assert(std::is_same<decltype(des::meta::options::get(opt3, key::test1)),
                                        A>::value, "");
    static_assert(std::is_same<decltype(des::meta::options::get(opt3, key::test2)),
                                        B>::value, "");
    static_assert(std::is_same<decltype(des::meta::options::get(opt3, key::test3)),
                                        C>::value, "");

    auto opt4 = des::meta::options::set(opt3, key::test1, B{});

    static_assert(des::meta::options::size(opt4) == 3, "");
    static_assert(std::is_same<decltype(des::meta::options::get(opt4, key::test1)),
                                        B>::value, "");
    static_assert(std::is_same<decltype(des::meta::options::get(opt4, key::test2)),
                                        B>::value, "");
    static_assert(std::is_same<decltype(des::meta::options::get(opt4, key::test3)),
                                        C>::value, "");
}
