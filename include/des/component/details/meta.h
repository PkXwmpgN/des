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

#ifndef __DES_COMPONENT_DETAILS_META_H_INCLUDED__
#define __DES_COMPONENT_DETAILS_META_H_INCLUDED__

#include <cstddef>

DES_COMPONENT_DETAILS_BEGIN

struct metadata
{
    void owner(size_t own) noexcept { owner_ = own; }
    auto owner() const noexcept { return owner_; }

private:

    size_t owner_ = 0;
};

struct meta_data_maker
{
    template<typename _Config>
    auto make_data(const _Config &) const noexcept;
};

template<typename _Components>
struct meta_maker
{
    template<typename _Config>
    auto make_meta(const _Config & config) const noexcept;
};

DES_COMPONENT_DETAILS_END

#endif // __DES_COMPONENT_DETAILS_META_H_INCLUDED__
