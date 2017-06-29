/*
The MIT License (MIT)
Copyright (c) 2017 Alexey Yegorov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

#include <tuple>
#include <utility>

#include "des/meta/algorithm.h"

DES_CONTEXT_DETAILS_BEGIN

namespace /* anonymous */
{
    namespace keys
    {
        constexpr auto fixed = meta::size_v<0>;
        constexpr auto capacity = meta::size_v<1>;
    }

    template<typename _Data, typename _Key, typename _Value>
    auto set(_Data && data, _Key && key, _Value && value)
    {
        auto result = meta::copy(data, [](auto && element)
        {
            using nkey = std::decay_t<_Key>;
            using okey = std::decay_t<decltype(std::get<0>(element))>;
            using same = std::is_same<nkey, okey>;
            return meta::bool_constant<!same::value>{};
        });

        return std::tuple_cat(result, std::make_tuple(std::make_pair(key, value)));
    }

    template<typename _Data, typename _Key>
    auto get(_Data && data, _Key &&)
    {
        auto result = meta::get(data, [](auto && element)
        {
            using nkey = std::decay_t<_Key>;
            using okey = std::decay_t<decltype(std::get<0>(element))>;
            return std::is_same<nkey, okey>{};
        });

        using result_type = std::decay_t<decltype(result)>;
        static_assert(std::tuple_size<result_type>::value == 1, "");

        auto index = std::get<0>(result);
        auto element = std::get<index>(data);
        return std::get<1>(element);
    }
}

template<typename _Data>
template<size_t _Capacity>
constexpr auto config<_Data>::
    fixed_entity(meta::size<_Capacity> capacity) const noexcept
{
    using type1 = decltype(set(data_, keys::fixed, meta::true_v));
    using type2 = decltype(set(type1{}, keys::capacity, capacity));
    return config<type2>{};
}

template<typename _Data>
template<size_t _Capacity>
constexpr auto config<_Data>::
    dynamic_entity(meta::size<_Capacity> capacity) const noexcept
{
    using type1 = decltype(set(data_, keys::fixed, meta::false_v));
    using type2 = decltype(set(type1{}, keys::capacity, capacity));
    return config<type2>{};
}

template<typename _Data>
constexpr auto config<_Data>::fixed() const noexcept
{
    using result = decltype(get(data_, keys::fixed));
    return result{};
}

template<typename _Data>
constexpr auto config<_Data>::capacity() const noexcept
{
    using result = decltype(get(data_, keys::capacity));
    return result{};
}

template<typename... _Values>
inline constexpr auto make_config(_Values...) noexcept
{
    return config<std::tuple<_Values...>>{};
}

inline constexpr auto make_default_config() noexcept
{
    return make_config(std::make_pair(keys::fixed, meta::true_v),
                       std::make_pair(keys::capacity, meta::size_v<1024>));
}

DES_CONTEXT_DETAILS_END
