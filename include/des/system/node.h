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

#ifndef __DES_SYSTEM_NODE_H_INCLUDED__
#define __DES_SYSTEM_NODE_H_INCLUDED__

#include <utility>
#include <tuple>

#include "names.h"
#include "details/node.h"
#include "details/node.inl"
#include "details/sequence.h"
#include "details/sequence.inl"

DES_SYSTEM_BEGIN

template<typename _System>
inline constexpr auto make_node(_System && system) noexcept
{
    return details::make_node(std::forward<_System>(system));
}

template<typename... _Nodes>
inline constexpr auto make_sequence(_Nodes && ... nodes)
{
    return details::make_sequence(std::forward<_Nodes>(nodes)...);
}

DES_SYSTEM_END

#endif // __DES_SYSTEM_NODE_H_INCLUDED__
