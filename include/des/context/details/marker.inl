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

#include "des/meta/algorithm.h"

DES_CONTEXT_DETAILS_BEGIN

template<typename _Components>
inline constexpr auto marker<_Components>::size() const noexcept
{
    return bits_.size();
}

template<typename _Components>
template<typename _Component>
void marker<_Components>::set(_Component && component) noexcept
{
    auto index = get_index(std::forward<_Component>(component));
    bits_.set(index, true);
}

template<typename _Components>
template<typename _Component>
void marker<_Components>::reset(_Component && component) noexcept
{
    auto index = get_index(std::forward<_Component>(component));
    bits_.set(index, false);
}

template<typename _Components>
template<typename _Component>
auto marker<_Components>::test(_Component && component) const noexcept
{
    auto index = get_index(std::forward<_Component>(component));
    return bits_.test(index);
}

template<typename _Components>
template<typename _Component>
constexpr auto marker<_Components>::get_index(_Component &&) const noexcept
{
    constexpr auto list = componet_list_type{};
    auto output = des::meta::get(list, [](auto & elem)
    {
        return std::is_same<std::decay_t<decltype(elem)>,
                            std::decay_t<_Component>>{};
    });
    return std::get<0>(output);
}

template<typename _Marker, typename... _Components>
inline void fill_marker(_Marker && marker, _Components && ... components)
{
    auto list = std::make_tuple(std::forward<_Components>(components)...);
    meta::foreach(list, [&marker](const auto & elem)
    {
        marker.set(elem);
    });
}

DES_CONTEXT_DETAILS_END
