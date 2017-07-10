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

#ifndef __DES_ENTITY_DETAILS_STORAGE_H_INCLUDED__
#define __DES_ENTITY_DETAILS_STORAGE_H_INCLUDED__

#include <vector>
#include <queue>

#include "identificator.h"

DES_ENTITY_DETAILS_BEGIN

struct storage_identificator_tag{};
constexpr auto storage_identificator = storage_identificator_tag{};

template<typename _Data>
struct storage
{
public:

    using data_type = _Data;
    using index_type = typename data_type::index_type;
    using identificator_type = identificator<index_type, storage_identificator_tag>;

    decltype(auto) get(identificator_type ide) const noexcept;
    decltype(auto) get(identificator_type ide) noexcept;

    auto add();
    auto size() const noexcept;

private:

    data_type data_;
    index_type active_ = 0;
};

template<typename _Buffer>
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

DES_ENTITY_DETAILS_END

#endif // __DES_ENTITY_DETAILS_STORAGE_H_INCLUDED__
