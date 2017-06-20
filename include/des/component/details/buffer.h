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

#ifndef __DES_COMPONENT_DETAILS_BUFFER_H_INCLUDED__
#define __DES_COMPONENT_DETAILS_BUFFER_H_INCLUDED__

#include <type_traits>
#include <array>
#include <vector>

#include "des/meta/statement.h"

DES_COMPONENT_DETAILS_BEGIN

template<typename _Self, typename _Components>
struct buffer_base
{
public:

    using components_list = _Components;
    using self_type = _Self;

    template<typename _Component, typename _Id>
    decltype(auto) get(_Component component, _Id ide) const noexcept;

    template<typename _Component, typename _Id>
    decltype(auto) get(_Component component, _Id ide) noexcept;

private:

    decltype(auto) self() const noexcept;
    decltype(auto) self() noexcept;
};

template<typename _Components, typename _Capacity>
struct buffer_fixed final :
    buffer_base<buffer_fixed<_Components, _Capacity>, _Components>
{
    using base_type = buffer_base<buffer_fixed<_Components, _Capacity>, _Components>;
    using components_list = typename base_type::components_list;
private:

    decltype(auto) data() const noexcept { return data_; }
    decltype(auto) data() noexcept { return data_; }

private:

    std::array<_Components, _Capacity::value> data_;
};

template<typename _Components, typename _Capacity>
struct buffer_dynamic final :
    buffer_base<buffer_dynamic<_Components, _Capacity>, _Components>
{
    using base_type = buffer_base<buffer_fixed<_Components, _Capacity>, _Components>;
    using components_list = typename base_type::components_list;

    buffer_dynamic();

private:

    decltype(auto) data() const noexcept { return data_; }
    decltype(auto) data() noexcept { return data_; }

private:

    std::vector<_Components> data_;
};

template<typename _Components>
struct buffer_maker
{
    template<typename _Config>
    constexpr auto make(_Config cfg) noexcept;
};

DES_COMPONENT_DETAILS_END

#endif // __DES_COMPONENT_DETAILS_BUFFER_H_INCLUDED__
