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

#include <utility>
#include <array>
#include <tuple>
#include "des/core/buffer.h"

DES_COMPONENT_DETAILS_BEGIN

template<typename _Config>
auto meta_data_maker::make_data(const _Config &) const noexcept
{
    return metadata{};
}

template<typename _Components>
template<typename _Config>
auto meta_maker<_Components>::make_meta(const _Config & config) const noexcept
{
    using data_maker_type = meta_data_maker;
    using buffer_meker_type = core::details::buffer_maker<data_maker_type>;
    using buffer_type = decltype(std::declval<buffer_meker_type>().make(config));
    return std::array<buffer_type, std::tuple_size<_Components>::value>{};
}

DES_COMPONENT_DETAILS_END
