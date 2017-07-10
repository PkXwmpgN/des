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

DES_COMPONENT_DETAILS_BEGIN

template<typename _Components>
template<typename _Component>
inline void index<_Components>::set(_Component && component, value_type value) noexcept
{
    index_[get_index(std::forward<_Component>(component))] = value;
}

template<typename _Components>
template<typename _Component>
decltype(auto) index<_Components>::increase(_Component && component) noexcept
{
    return ++index_[get_index(std::forward<_Component>(component))];
}

template<typename _Components>
template<typename _Component>
decltype(auto) index<_Components>::decrease(_Component && component) noexcept
{
    return --index_[get_index(std::forward<_Component>(component))];
}

template<typename _Components>
template<typename _Component>
inline decltype(auto) index<_Components>::get(_Component && component) const noexcept
{
    return index_[get_index(std::forward<_Component>(component))];
}

template<typename _Components>
template<typename _Component>
inline void index<_Components>::reset(_Component && component) noexcept
{
    set(std::forward<_Component>(component), invalid_index_value<value_type>);
}

template<typename _Components>
template<typename _Component>
inline auto index<_Components>::test(_Component && component) const noexcept
{
    return index_[get_index(std::forward<_Component>(component))] !=
           invalid_index_value<value_type>;
}

template<typename _Components>
inline void index<_Components>::reset() noexcept
{
    fill(invalid_index_value<value_type>);
}

template<typename _Components>
inline void index<_Components>::fill(value_type value) noexcept
{
    index_.fill(value);
}

template<typename _Components>
template<typename _Component>
inline decltype(auto) index<_Components>::get_index(_Component &&) const noexcept
{
    auto output = des::meta::get(componet_list_type{}, [](auto & elem)
    {
        return std::is_same<std::decay_t<decltype(elem)>,
                            std::decay_t<_Component>>{};
    });
    return std::get<0>(output);
}

DES_COMPONENT_DETAILS_END
