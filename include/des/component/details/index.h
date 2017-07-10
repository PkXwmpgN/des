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

#ifndef __DES_COMPONENT_DETAILS_INDEX_H_INCLUDED__
#define __DES_COMPONENT_DETAILS_INDEX_H_INCLUDED__

#include <array>
#include <tuple>
#include <utility>
#include <limits>

DES_COMPONENT_DETAILS_BEGIN

template<typename _Integral>
constexpr auto invalid_index_value = std::numeric_limits<_Integral>::max();

template<typename _Components>
struct index
{
    using componet_list_type = _Components;
    using value_type = size_t;
    using index_type = std::array<value_type, std::tuple_size<componet_list_type>::value>;

    index() { reset(); }
    void reset() noexcept;
    void fill(value_type value) noexcept;

    template<typename _Component>
    void set(_Component && component, value_type value) noexcept;

    template<typename _Component>
    decltype(auto) increase(_Component && component) noexcept;

    template<typename _Component>
    decltype(auto) decrease(_Component && component) noexcept;

    template<typename _Component>
    decltype(auto) get(_Component && component) const noexcept;

    template<typename _Component>
    void reset(_Component && component) noexcept;

    template<typename _Component>
    auto test(_Component && component) const noexcept;

private:

    template<typename _Component>
    decltype(auto) get_index(_Component && component) const noexcept;

private:

    index_type index_;
};

template<typename _Components>
struct index_maker
{
    auto make() const noexcept
    {
        return index<_Components>{};
    }
};

DES_COMPONENT_DETAILS_END

#endif // __DES_COMPONENT_DETAILS_INDEX_H_INCLUDED__
