#include <tuple>
#include <des/meta/types.h>
#include <des/meta/algorithm.h>

struct A {};

template<typename _T>
struct B {};

int main()
{
    // transform

    auto result = des::meta::transform(std::make_tuple(A{}, 0.1, 1), [](auto & el)
    {
        return B<std::decay_t<decltype(el)>>{};
    });

    using result_type = std::decay_t<decltype(result)>;
    static_assert(std::is_same<std::tuple_element_t<0, result_type>, B<A>>::value, "");
    static_assert(std::is_same<std::tuple_element_t<1, result_type>, B<double>>::value, "");
    static_assert(std::is_same<std::tuple_element_t<2, result_type>, B<int>>::value, "");

    // get

    auto get_result = des::meta::get(std::make_tuple(A{}, 0.1, 1), [](auto & elem)
    {
        return std::is_same<std::decay_t<decltype(elem)>, A>{};
    });

    using get_result_tupe = std::decay_t<decltype(get_result)>;
    static_assert(std::tuple_size<get_result_tupe>::value == 1, "");
    static_assert(std::is_same<std::tuple_element_t<0, get_result_tupe>, A>::value, "");
}
