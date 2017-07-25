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

#include "des/meta/options.h"

DES_DATA_DETAILS_BEGIN

namespace /* anonymous */
{
    namespace keys
    {
        constexpr auto components = meta::options::key_v<0>;
        constexpr auto entities = meta::options::key_v<1>;
    }
}

template<typename _Data>
template<typename _Storage>
inline constexpr auto storage<_Data>::components(_Storage && stor) const noexcept
{
    using type = decltype(meta::options::set(data_, keys::components,
        std::forward<_Storage>(stor)));
    return storage<type>{};
}

template<typename _Data>
template<typename _Storage>
inline constexpr auto storage<_Data>::entities(_Storage && stor) const noexcept
{
    using type = decltype(meta::options::set(data_, keys::entities,
        std::forward<_Storage>(stor)));
    return storage<type>{};
}


template<typename _Data>
inline constexpr auto storage<_Data>::components() const noexcept
{
    using result = decltype(meta::options::get(data_, keys::components));
    return result{};
}

template<typename _Data>
inline constexpr auto storage<_Data>::entities() const noexcept
{
    using result = decltype(meta::options::get(data_, keys::entities));
    return result{};
}

inline constexpr auto make_storage() noexcept
{
    return storage<des::meta::options::empty_t>{};
}

DES_DATA_DETAILS_END
