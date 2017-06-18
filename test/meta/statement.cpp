#include <utility>
#include <cassert>
#include <des/meta/types.h>
#include <des/meta/statement.h>

struct A{};
struct B{};

template<typename _T>
constexpr auto is_A = std::is_same<A, std::decay_t<_T>>{};

template<typename _T>
bool test_A(_T)
{
    return des::meta::if_(is_A<_T>)
        .then_([](){ return true; })
        .else_([](){ return false; })();
}

int main()
{
    auto test0 = des::meta::if_(des::meta::true_v)
        .then_([](){ return A{}; })
        .else_([](){ return B{}; });

    auto test1 = des::meta::if_(des::meta::false_v)
        .then_([](){ return A{}; })
        .else_([](){ return B{}; });

    static_assert(std::is_same<A, std::decay_t<decltype(test0())>>::value, "");
    static_assert(std::is_same<B, std::decay_t<decltype(test1())>>::value, "");

    assert(test_A(A{}));
    assert(!test_A(B{}));
}
