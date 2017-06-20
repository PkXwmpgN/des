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

DES_COMPONENT_DETAILS_BEGIN

template<typename _Self, typename _Components>
template<typename _Component, typename _Id>
inline decltype(auto) buffer_base<_Self, _Components>::get(_Component component,
        _Id ide) const noexcept
{
    assert(ide.value() < self().data().size());

    using component_type = std::decay_t<decltype(component)>;
    return std::get<component_type>(self().data()[ide.value]);
}

template<typename _Self, typename _Components>
template<typename _Component, typename _Id>
inline decltype(auto) buffer_base<_Self, _Components>::get(_Component component,
        _Id ide) noexcept
{
    assert(ide.value() < self().data().size());

    using component_type = std::decay_t<decltype(component)>;
    return std::get<component_type>(self().data()[ide.value]);
}

template<typename _Self, typename _Components>
inline decltype(auto) buffer_base<_Self, _Components>::self() const noexcept
{
    return static_cast<const self_type&>(*this);
}

template<typename _Self, typename _Components>
inline decltype(auto) buffer_base<_Self, _Components>::self() noexcept
{
    return static_cast<self_type&>(*this);
}

template<typename _Components, typename _Capacity>
inline buffer_dynamic<_Components, _Capacity>::buffer_dynamic()
{
    data_.reserve(_Capacity::value);
}

template<typename _Components>
template<typename _Config>
inline constexpr auto buffer_maker<_Components>::make(_Config cfg) noexcept
{
    return meta::if_(cfg.fixed())
        .then_([](auto cfg)
        {
            using capacity_type = std::decay_t<decltype(cfg.capacity())>;
            return buffer_fixed<_Components, capacity_type>{};
        })
        .else_([](auto cfg)
        {
            using capacity_type = std::decay_t<decltype(cfg.capacity())>;
            return buffer_dynamic<_Components, capacity_type>{};
        })(cfg);
}

DES_COMPONENT_DETAILS_END
