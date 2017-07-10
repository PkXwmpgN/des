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

#include "des/meta/statement.h"

DES_COMPONENT_DETAILS_BEGIN

template<typename _Data, typename _Capacity>
template<typename _Component>
inline decltype(auto) buffer_fixed<_Data, _Capacity>::get(_Component &&,
        index_type value) const noexcept
{
    using component_type = std::decay_t<_Component>;
    return std::get<component_type>(data_[value]);
}

template<typename _Data, typename _Capacity>
template<typename _Component>
inline decltype(auto) buffer_fixed<_Data, _Capacity>::get(_Component &&,
        index_type value) noexcept
{
    using component_type = std::decay_t<_Component>;
    return std::get<component_type>(data_[value]);
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
template<typename _Component>
inline decltype(auto) buffer_dynamic<_Data, _Capacity>::get(_Component &&,
        index_type value) const noexcept
{
    using component_type = std::decay_t<_Component>;
    return std::get<component_type>(data_[value]);
}

template<typename _Data, typename _Capacity>
template<typename _Component>
inline decltype(auto) buffer_dynamic<_Data, _Capacity>::get(_Component &&,
        index_type value) noexcept
{
    using component_type = std::decay_t<_Component>;
    return std::get<component_type>(data_[value]);
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

template<typename... _Components>
inline auto buffer_data_maker<_Components...>::make() const noexcept
{
    return std::tuple<_Components...>{};
}

template<typename _Maker>
template<typename _Config>
inline auto buffer_maker<_Maker>::make_buffer(const _Config & cfg) const noexcept
{
    using capacity_type = decltype(cfg.capacity());
    using data_type = decltype(std::declval<_Maker>().make());
    return meta::if_(cfg.fixed())
        .then_([](){ return buffer_fixed<data_type, capacity_type>{}; })
        .else_([](){ return buffer_dynamic<data_type, capacity_type>{}; })();
}

template<typename _Maker>
inline auto buffer_maker<_Maker>::make_component_list() const noexcept
{
    return _Maker{}.make();
}

DES_COMPONENT_DETAILS_END
