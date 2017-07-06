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

DES_COMPONENT_DETAILS_BEGIN

namespace /* anonymous */
{
    template<typename _Buffer, typename _Component>
    constexpr auto contains_v = meta::is_tuple_contains<std::decay_t<_Component>,
                                        typename std::decay_t<_Buffer>::data_type>{};

    template<typename _Component, typename _Data>
    inline decltype(auto) get_buffer(_Component && component, _Data && data) noexcept
    {
        auto result = meta::get(data, [&component](auto && buffer)
        {
            return contains_v<decltype(buffer), decltype(component)>;
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

template<typename... _Buffers>
template<typename _Config>
inline auto storage_data_maker<_Buffers...>::make(const _Config & config) const noexcept
{
    auto list = std::make_tuple(_Buffers{}...);
    return meta::transform(list, [&config](auto & buffer)
    {
        return buffer.make(config);
    });
}

template<typename _Maker>
template<typename _Config>
inline auto storage_maker<_Maker>::make(const _Config & config) const noexcept
{
    using data_type = decltype(std::declval<_Maker>().make(config));
    return storage<data_type>{};
}



DES_COMPONENT_DETAILS_END
