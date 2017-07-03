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

#ifndef __DES_META_OPTIONS_H_INCLUDED__
#define __DES_META_OPTIONS_H_INCLUDED__

#include <tuple>
#include <type_traits>

#include "names.h"
#include "types.h"
#include "algorithm.h"

DES_META_OPTIONS_BEGIN

template<std::size_t _Size>
constexpr auto key_v = size<_Size>{};

using empty = std::tuple<>;
constexpr auto empty_v = empty{};

template<typename _Data, typename _Key, typename _Value>
inline auto set(_Data && data, _Key && key, _Value && value)
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
inline auto get(_Data && data, _Key &&)
{
    auto result = meta::get(data, [](auto && element)
    {
        using nkey = std::decay_t<_Key>;
        using okey = std::decay_t<decltype(std::get<0>(element))>;
        return std::is_same<nkey, okey>{};
    });

    auto index = std::get<0>(result);
    auto element = std::get<index>(data);
    return std::get<1>(element);
}

template<typename _Data>
inline constexpr auto size(_Data &&) noexcept
{
    return std::tuple_size<std::decay_t<_Data>>::value;
}

DES_META_OPTIONS_END

#endif // __DES_META_OPTIONS_H_INCLUDED__
