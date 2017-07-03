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

#ifndef __DES_COMPONENT_DETAILS_MARKER_H_INCLUDED__
#define __DES_COMPONENT_DETAILS_MARKER_H_INCLUDED__

#include <bitset>
#include <tuple>
#include <utility>

DES_COMPONENT_DETAILS_BEGIN

template<typename _Components>
struct marker
{
    using componet_list_type = _Components;
    using bits_type = std::bitset<std::tuple_size<componet_list_type>::value>;

    constexpr auto size() const noexcept;

    template<typename _Component>
    void set(_Component && component) noexcept;

    template<typename _Component>
    void reset(_Component && component) noexcept;

    template<typename _Component>
    auto test(_Component && component) const noexcept;

    void reset() noexcept;

private:

    template<typename _Component>
    constexpr auto get_index(_Component && component) const noexcept;

private:

    bits_type bits_;
};

template<typename... _Components>
inline constexpr auto make_marker(_Components && ... components)
{
    auto list = std::make_tuple(std::forward<_Components>(components)...);
    return marker<std::decay_t<decltype(list)>>{};
}

template<typename _Marker, typename... _Components>
inline void fill_marker(_Marker && marker, _Components && ... components);

DES_COMPONENT_DETAILS_END

#endif // __DES_COMPONENT_DETAILS_MARKER_H_INCLUDED__
