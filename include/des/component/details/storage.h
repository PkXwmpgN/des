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

#include "des/meta/types.h"

DES_COMPONENT_DETAILS_BEGIN

template<typename _Data>
struct storage
{
public:

    template<typename _Component, typename _Id>
    decltype(auto) get(_Component && comp, _Id && id) noexcept;

    template<typename _Component, typename _Id>
    decltype(auto) get(_Component && comp, _Id && id) const noexcept;

private:

    _Data data_;
};

template<typename... _Buffers>
struct storage_data_maker
{
    template<typename _Config>
    auto make(const _Config & config) const noexcept;
};

template<typename _Maker>
struct storage_maker
{
    template<typename _Config>
    auto make(const _Config & config) const noexcept;
};

DES_COMPONENT_DETAILS_END

#endif // __DES_COMPONENT_DETAILS_STORAGE_H_INCLUDED__
