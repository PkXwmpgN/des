#include <tuple>
#include <des/meta/types.h>
#include <des/meta/algorithm.h>

struct A {};

template<typename _T>
struct B {};

int main()
{
    auto result = des::meta::transform(std::make_tuple(A{}, 0.1, 1), [](auto & el)
    {
        return B<std::decay_t<decltype(el)>>{};
    });

    using result_type = std::decay_t<decltype(result)>;
    static_assert(std::is_same<std::tuple_element_t<0, result_type>, B<A>>::value, "");
    static_assert(std::is_same<std::tuple_element_t<1, result_type>, B<double>>::value, "");
    static_assert(std::is_same<std::tuple_element_t<2, result_type>, B<int>>::value, "");
}
