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

#ifndef __DES_META_TRAITS_H_INCLUDED__
#define __DES_META_TRAITS_H_INCLUDED__

#include <utility>
#include "names.h"
#include "details/tuple_contains.h"
#include "details/type_specialization.h"

DES_META_BEGIN

template <template<typename...> class _Template, typename _Type>
using is_specialization_of_t = typename details::is_specialization_of<_Template, _Type>::type;

template <template<typename...> class _Template, typename _Type>
constexpr auto is_specialization_of_v = is_specialization_of_t<_Template, _Type>{};

template<typename _Type, typename _Tuple>
using is_tuple_contains_t = typename details::tuple_contains_type
<
    std::decay_t<_Type>,
    std::decay_t<_Tuple>
>::type;

template<typename _Type, typename _Tuple>
constexpr auto is_tuple_contains_v = is_tuple_contains_t<_Type, _Tuple>{};

DES_META_END

#endif // __DES_META_TRAITS_H_INCLUDED__
