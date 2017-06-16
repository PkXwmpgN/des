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

#ifndef __DES_META_DETAILS_TUPLE_APPLY_H_INCLUDED__
#define __DES_META_DETAILS_TUPLE_APPLY_H_INCLUDED__

#include <utility>

DES_META_DETAILS_BEGIN

template<typename _Function, size_t... _Is>
inline constexpr auto apply_index_impl(_Function fn, std::index_sequence<_Is...>) noexcept
{
    return fn(std::integral_constant<size_t, _Is> {}...);
}

template<size_t _N, typename _Function>
inline constexpr auto apply_index(_Function fn) noexcept
{
    return apply_index_impl(fn, std::make_index_sequence<_N>{});
}

DES_META_DETAILS_END

#endif // __DES_META_DETAILS_TUPLE_APPLY_H_INCLUDED__
