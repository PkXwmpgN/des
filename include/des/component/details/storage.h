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

#ifndef __DES_COMPONENT_DETAILS_STORAGE_H_INCLUDED__
#define __DES_COMPONENT_DETAILS_STORAGE_H_INCLUDED__

#include "config.h"
#include "des/meta/algorithm.h"
#include "des/meta/types.h"

DES_COMPONENT_DETAILS_BEGIN

template<typename _Data>
struct storage
{

};

template<typename _Config>
struct storage_generator
{
    template<typename _Buffer>
    constexpr auto operator()(_Buffer buffer) const noexcept
    {
        return buffer.make(_Config{});
    }
};

template<typename _Buffers>
struct storage_maker
{
    template<size_t _Capacity>
    constexpr auto fixed(meta::size<_Capacity> capacity) const noexcept
    {
        constexpr auto cfg = make_config(meta::true_v, capacity);
        return decltype(make_storage(cfg)){};
    }

    template<size_t _Capacity>
    constexpr auto dynamic(meta::size<_Capacity> capacity) const noexcept
    {
        constexpr auto cfg = make_config(meta::false_v, capacity);
        return decltype(make_storage(cfg)){};
    }

private:

    template<typename _Config>
    auto make_storage(_Config) const noexcept
    {
        auto data = meta::transform(_Buffers{}, storage_generator<_Config>{});
        return storage<decltype(data)>{};
    }
};

DES_COMPONENT_DETAILS_END

#endif // __DES_COMPONENT_DETAILS_STORAGE_H_INCLUDED__