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

#ifndef __DES_META_ALGORITHM_H_INCLUDED__
#define __DES_META_ALGORITHM_H_INCLUDED__

#include <tuple>

#include "names.h"
#include "statement.h"
#include "details/tuple_apply.h"

DES_META_BEGIN

template<typename _Tuple, typename _Function>
inline constexpr auto transform(_Tuple tuple, _Function fn) noexcept
{
    return details::apply_index<std::tuple_size<_Tuple>{}>([&](auto... Is)
    {
        return std::make_tuple(fn(std::get<Is>(tuple))...);
    });
}

template<typename _Tuple, typename _Predicate>
inline constexpr auto get(_Tuple && tuple, _Predicate && pred) noexcept
{
    return details::apply_index<std::tuple_size<_Tuple>{}>([&](auto... Is)
    {
        return std::tuple_cat([](auto && value, auto && pred)
        {
            return if_(pred(value))
                .then_([&value](){ return std::make_tuple(value); })
                .else_([](){ return std::make_tuple(); })();
        }(std::get<Is>(tuple), pred)...);
    });
}

DES_META_END

#endif // __DES_META_ALGORITHM_H_INCLUDED__
