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

#include <cassert>
#include <type_traits>

#include "entity.h"
#include "entity.inl"
#include "des/meta/statement.h"

DES_ENTITY_DETAILS_BEGIN

template<typename _Data, typename _Capacity>
inline decltype(auto) buffer_fixed<_Data, _Capacity>::get(index_type value) const noexcept
{
    return data_[value];
}

template<typename _Data, typename _Capacity>
inline decltype(auto) buffer_fixed<_Data, _Capacity>::get(index_type value) noexcept
{
    return data_[value];
}

template<typename _Data, typename _Capacity>
inline auto buffer_fixed<_Data, _Capacity>::size() const noexcept
{
    return data_.size();
}

template<typename _Data, typename _Capacity>
inline void buffer_fixed<_Data, _Capacity>::resize(index_type value)
{
    assert(value <= size());
}

template<typename _Data, typename _Capacity>
inline decltype(auto) buffer_dynamic<_Data, _Capacity>::get(index_type value) const noexcept
{
    return data_[value];
}

template<typename _Data, typename _Capacity>
inline decltype(auto) buffer_dynamic<_Data, _Capacity>::get(index_type value) noexcept
{
    return data_[value];
}

template<typename _Data, typename _Capacity>
inline auto buffer_dynamic<_Data, _Capacity>::size() const noexcept
{
    return data_.size();
}

template<typename _Data, typename _Capacity>
inline void buffer_dynamic<_Data, _Capacity>::resize(index_type value)
{
    if(size() <= value)
        data_.resize(data_.size() + value * 1.6);
}

template<typename _Index>
template<typename _Config>
auto data_maker<_Index>::make(const _Config &) const noexcept
{
    using index_type = decltype(std::declval<_Index>().make());
    return entity<index_type>{};
}

template<typename _Maker>
template<typename _Config>
inline auto buffer_maker<_Maker>::make(const _Config & cfg) const noexcept
{
    using capacity_type = decltype(cfg.capacity());
    using data_type = decltype(std::declval<_Maker>().make(cfg));
    return meta::if_(cfg.fixed())
        .then_([]() { return buffer_fixed<data_type, capacity_type>{}; })
        .else_([]() { return buffer_dynamic<data_type, capacity_type>{}; })();
}

DES_ENTITY_DETAILS_END
