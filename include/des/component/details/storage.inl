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
#include <cassert>
#include <type_traits>

#include "des/meta/traits.h"
#include "des/meta/algorithm.h"

#include "index.h"
#include "index.inl"

#include "meta.h"
#include "meta.inl"

DES_COMPONENT_DETAILS_BEGIN

namespace /* anonymous */
{
    template<typename _Buffer, typename _Component>
    constexpr auto contains_v = meta::is_tuple_contains_v<std::decay_t<_Component>,
                                        typename std::decay_t<_Buffer>::value_type>;

    template<typename _Component, typename _Data>
    inline decltype(auto) get_buffer(_Component && component, _Data && data) noexcept
    {
        auto result = meta::get(data, [&component](auto && buffer)
        {
            return contains_v<decltype(buffer), decltype(component)>;
        });

        auto index = std::get<0>(result);
        return std::get<index>(data);
    }

    template<typename _Component, typename _Index, typename _Data>
    inline decltype(auto) get_component(_Component && component,
        _Index && index, _Data && data) noexcept
    {
        using component_type = std::decay_t<_Component>;
        return std::get<component_type>(get_buffer(component, data).get(index));
    }
}

template<typename _Data, typename _Meta, typename _Index>
inline storage<_Data, _Meta, _Index>::storage()
{
    index_.fill(0);
}

template<typename _Data, typename _Meta, typename _Index>
template<typename _Component>
inline decltype(auto) storage<_Data, _Meta, _Index>::
    get(_Component && comp, index_type value) const noexcept
{
    assert(value < size(comp));
    return get_component(comp, value, data_);
}

template<typename _Data, typename _Meta, typename _Index>
template<typename _Component>
inline decltype(auto) storage<_Data, _Meta, _Index>::
    get(_Component && comp, index_type value) noexcept
{
    assert(value < size(comp));
    return get_component(comp, value, data_);
}

template<typename _Data, typename _Meta, typename _Index>
template<typename _Component>
decltype(auto) storage<_Data, _Meta, _Index>::
    meta(_Component && comp, index_type value) noexcept
{
    assert(value < size(comp));
    return meta_[index_.id(comp)].get(value);
}

template<typename _Data, typename _Meta, typename _Index>
template<typename _Component>
decltype(auto) storage<_Data, _Meta, _Index>::
    meta(_Component && comp, index_type value) const noexcept
{
    assert(value < size(comp));
    return meta_[index_.id(comp)].get(value);
}

template<typename _Data, typename _Meta, typename _Index>
template<typename _Component>
inline auto storage<_Data, _Meta, _Index>::add(_Component && comp)
{
    auto & buffer = get_buffer(comp, data_);
    auto & meta = meta_[index_.id(comp)];
    auto current_index = index_.get(comp);
    auto next_index = index_.increase(comp);
    buffer.resize(next_index);
    meta.resize(next_index);
    return current_index;
}

template<typename _Data, typename _Meta, typename _Index>
template<typename _Component>
inline auto storage<_Data, _Meta, _Index>::remove(_Component && comp, index_type value)
{
    assert(value < size(comp));
    if(auto index = index_.decrease(comp))
    {
        auto & buffer = get_buffer(comp, data_);
        auto & meta = meta_[index_.id(comp)];
        std::swap(buffer.get(value), buffer.get(index));
        std::swap(meta.get(value), meta.get(index));
        return true;
    }
    return false;
}

template<typename _Data, typename _Meta, typename _Index>
template<typename _Component>
inline auto storage<_Data, _Meta, _Index>::size(_Component && comp) const noexcept
{
    return index_.get(std::forward<_Component>(comp));
}

template<typename... _Buffers>
template<typename _Config>
inline auto storage_data_maker<_Buffers...>::make_data(const _Config & config) const noexcept
{
    auto list = std::make_tuple(_Buffers{}...);
    return meta::transform(list, [&config](auto & buffer)
    {
        return buffer.make_buffer(config);
    });
}

template<typename... _Buffers>
inline auto storage_data_maker<_Buffers...>::make_component_list() const noexcept
{
    auto list = std::make_tuple(_Buffers{}...);
    auto components = meta::transform(list, [](auto & buffer)
    {
        return buffer.make_component_list();
    });
    return meta::cat(components);
}

template<typename _Maker>
template<typename _Config>
inline constexpr auto storage_maker<_Maker>::make(const _Config & config) const noexcept
{
    using data_type = decltype(std::declval<_Maker>().make_data(config));
    using component_list_type = decltype(std::declval<_Maker>().make_component_list());

    using index_maker_type = index_maker<component_list_type>;
    using index_type = decltype(std::declval<index_maker_type>().make());

    using meta_maker_type = meta_maker<component_list_type>;
    using meta_type = decltype(std::declval<meta_maker_type>().make_meta(config));

    return storage<data_type, meta_type, index_type>{};
}

template<typename _Maker>
inline constexpr auto storage_maker<_Maker>::index() const noexcept
{
    using component_list_type = decltype(std::declval<_Maker>().make_component_list());
    return index_maker<component_list_type>{};
}

DES_COMPONENT_DETAILS_END
