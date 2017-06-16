#include <tuple>
#include <des/meta/types.h>
#include <des/meta/traits.h>

struct A {};

template<typename _T>
struct B {};

int main()
{
    // is_specialization_of

    static_assert(des::meta::is_specialization_of_v<B, B<int>>, "");
    static_assert(!des::meta::is_specialization_of_v<B, int>, "");
    static_assert(std::is_same<des::meta::is_specialization_of<B, B<int>>,
                               des::meta::true_type>::value, "");

    // is_tuple_contains

    using tuple_type = std::tuple<A, double, int>;

    static_assert(des::meta::is_tuple_contains_v<A, tuple_type>, "");
    static_assert(des::meta::is_tuple_contains_v<double, tuple_type>, "");
    static_assert(des::meta::is_tuple_contains_v<int, tuple_type>, "");
    static_assert(!des::meta::is_tuple_contains_v<char, tuple_type>, "");
    static_assert(std::is_same<des::meta::is_tuple_contains<A, tuple_type>,
                               des::meta::true_type>::value, "");
}
