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

#ifndef __DES_META_TYPES_H_INCLUDED__
#define __DES_META_TYPES_H_INCLUDED__

#include <utility>
#include <cstddef>
#include "names.h"

DES_META_BEGIN

template<typename _Type, _Type _Value>
using constant_t = std::integral_constant<_Type, _Value>;

template<typename _Type, _Type _Value>
constexpr auto constant_v = constant_t<_Type, _Value>{};

template<std::size_t _Value>
using sz_t = constant_t<std::size_t, _Value>;

template<std::size_t _Size>
constexpr auto sz_v = sz_t<_Size>{};

template<bool _Value>
using bool_t = constant_t<bool, _Value>;

template<bool _Value>
constexpr auto bool_v = bool_t<_Value>{};

using true_t = bool_t<true>;
constexpr auto true_v = true_t{};

using false_t = bool_t<false>;
constexpr auto false_v = false_t{};

DES_META_END

#endif // __DES_META_TYPES_H_INCLUDED__
