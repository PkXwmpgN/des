#include <tuple>
#include <des/meta/types.h>
#include <des/meta/algorithm.h>

struct A
{
    A() = default;
    A(A&&) = default;
    A & operator=(A&&) = default;
    A(const A&) = delete;
    A & operator=(const A&) = delete;
};

template<typename _T>
struct B {};

struct C {};

int main()
{
    // transform
    {
        auto output = des::meta::transform(std::make_tuple(A{}, 0.1, 1), [](auto & el)
        {
            return B<std::decay_t<decltype(el)>>{};
        });

        using output_type = std::decay_t<decltype(output)>;
        static_assert(std::is_same<std::tuple_element_t<0, output_type>, B<A>>::value, "");
        static_assert(std::is_same<std::tuple_element_t<1, output_type>, B<double>>::value, "");
        static_assert(std::is_same<std::tuple_element_t<2, output_type>, B<int>>::value, "");
    }


    // get
    {
        auto input = std::make_tuple(A{}, 0.1, 1);
        using input_type = std::decay_t<decltype(input)>;

        auto output = des::meta::get(input, [](auto & elem)
        {
            return std::is_same<std::decay_t<decltype(elem)>, A>{};
        });
        using output_type = std::decay_t<decltype(output)>;

        static_assert(std::tuple_size<output_type>::value == 1, "");
        constexpr auto index = std::get<0>(output);

        static_assert(std::is_same<std::tuple_element_t<index, input_type>, A>::value, "");
    }

    // copy
    {
        auto output = des::meta::copy(std::make_tuple(C{}, 0.1, 1), [](auto & elem)
        {
            return std::is_same<std::decay_t<decltype(elem)>, C>{};
        });
        using output_type = std::decay_t<decltype(output)>;
        static_assert(std::tuple_size<output_type>::value == 1, "");
        static_assert(std::is_same<std::tuple_element_t<0, output_type>, C>::value, "");
    }
}
