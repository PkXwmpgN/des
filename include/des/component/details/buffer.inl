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

template<typename _Self, typename _Data>
template<typename _Component, typename _Id>
inline decltype(auto) buffer_base<_Self, _Data>::get(_Component &&,
        _Id && ide) const noexcept
{
    assert(ide.value() < self().data().size());

    using component_type = std::decay_t<_Component>;
    return std::get<component_type>(self().data()[ide.value()]);
}

template<typename _Self, typename _Data>
template<typename _Component, typename _Id>
inline decltype(auto) buffer_base<_Self, _Data>::get(_Component &&,
        _Id && ide) noexcept
{
    assert(ide.value() < self().data().size());

    using component_type = std::decay_t<_Component>;
    return std::get<component_type>(self().data()[ide.value()]);
}

template<typename _Self, typename _Data>
inline auto buffer_base<_Self, _Data>::size() const noexcept
{
    return self().data().size();
}

template<typename _Self, typename _Data>
inline decltype(auto) buffer_base<_Self, _Data>::self() const noexcept
{
    return static_cast<const self_type&>(*this);
}

template<typename _Self, typename _Components>
inline decltype(auto) buffer_base<_Self, _Components>::self() noexcept
{
    return static_cast<self_type&>(*this);
}

template<typename... _Components>
template<typename _Config>
inline constexpr auto data_maker<_Components...>::make(const _Config &) const noexcept
{
    return std::tuple<_Components...>{};
}

template<typename _Maker>
template<typename _Config>
inline auto buffer_maker<_Maker>::make(const _Config & cfg) const noexcept
{
    auto maker = _Maker{};

    using capacity_type = std::decay_t<decltype(cfg.capacity())>;
    using data_type = std::decay_t<decltype(maker.make(cfg))>;

    return meta::if_(cfg.fixed())
        .then_([](){ return buffer_fixed<data_type, capacity_type>{}; })
        .else_([](){ return buffer_dynamic<data_type, capacity_type>{}; })();
}

DES_COMPONENT_DETAILS_END
