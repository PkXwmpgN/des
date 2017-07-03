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
#include "des/meta/options.h"

DES_DATA_DETAILS_BEGIN

namespace /* anonymous */
{
    namespace keys
    {
        constexpr auto fixed = meta::options::key_v<0>;
        constexpr auto capacity = meta::options::key_v<1>;
    }
}

template<typename _Data>
template<size_t _Capacity>
constexpr auto config<_Data>::
    fixed_entity(meta::size<_Capacity> capacity) const noexcept
{
    using type1 = decltype(meta::options::set(data_, keys::fixed, meta::true_v));
    using type2 = decltype(meta::options::set(type1{}, keys::capacity, capacity));
    return config<type2>{};
}

template<typename _Data>
template<size_t _Capacity>
constexpr auto config<_Data>::
    dynamic_entity(meta::size<_Capacity> capacity) const noexcept
{
    using type1 = decltype(meta::options::set(data_, keys::fixed, meta::false_v));
    using type2 = decltype(meta::options::set(type1{}, keys::capacity, capacity));
    return config<type2>{};
}

template<typename _Data>
constexpr auto config<_Data>::fixed() const noexcept
{
    using result = decltype(meta::options::get(data_, keys::fixed));
    return result{};
}

template<typename _Data>
constexpr auto config<_Data>::capacity() const noexcept
{
    using result = decltype(meta::options::get(data_, keys::capacity));
    return result{};
}

inline constexpr auto make_default_config() noexcept
{
    return config<des::meta::options::empty>{}.fixed_entity(meta::size_v<1024>);
}

DES_DATA_DETAILS_END
