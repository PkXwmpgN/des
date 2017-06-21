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

#include "config.h"
#include "des/meta/algorithm.h"

DES_COMPONENT_DETAILS_BEGIN

namespace /* anonymous */
{
    template<typename _Component, typename _Data>
    inline decltype(auto) get_buffer(_Component &&, _Data && data) noexcept
    {
        auto result = meta::get(data, [](auto && buffer)
        {
            using buffer_type = std::decay_t<decltype(buffer)>;
            using buffer_component_list = typename buffer_type::component_list;
            return meta::is_tuple_contains<std::decay_t<_Component>, buffer_component_list>{};
        });

        using result_type = std::decay_t<decltype(result)>;
        static_assert(std::tuple_size<result_type>::value == 1, "");

        auto index = std::get<0>(result);
        return std::get<index>(data);
    }
}

template<typename _Data>
template<typename _Component, typename _Id>
inline decltype(auto) storage<_Data>::
    get(_Component && comp, _Id && id) const noexcept
{
    const auto & buffer = get_buffer(std::forward<_Component>(comp), data_);
    assert(id.value() < buffer.size());

    return buffer.get(std::forward<_Component>(comp),
                      std::forward<_Id>(id));
}

template<typename _Data>
template<typename _Component, typename _Id>
inline decltype(auto) storage<_Data>::
    get(_Component && comp, _Id && id) noexcept
{
    auto & buffer = get_buffer(std::forward<_Component>(comp), data_);
    assert(id.value() < buffer.size());

    return buffer.get(std::forward<_Component>(comp),
                      std::forward<_Id>(id));
}

template<typename _Buffers>
template<size_t _Capacity>
inline constexpr auto storage_maker<_Buffers>::
    fixed(meta::size<_Capacity> capacity) const noexcept
{
    constexpr auto cfg = make_config(meta::true_v, capacity);
    return decltype(make_storage(std::move(cfg))){};
}

template<typename _Buffers>
template<size_t _Capacity>
inline constexpr auto storage_maker<_Buffers>::
    dynamic(meta::size<_Capacity> capacity) const noexcept
{
    constexpr auto cfg = make_config(meta::false_v, capacity);
    return decltype(make_storage(std::move(cfg))){};
}

template<typename _Buffers>
template<typename _Config>
inline auto storage_maker<_Buffers>::
    make_storage(_Config && cfg) const noexcept
{
    decltype(auto) data = meta::transform(_Buffers{}, [&cfg](auto buffer)
    {
        return buffer.make(std::forward<_Config>(cfg));
    });
    return storage<std::decay_t<decltype(data)>>{};
}

DES_COMPONENT_DETAILS_END
