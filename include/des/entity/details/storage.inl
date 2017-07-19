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

#include <type_traits>

DES_ENTITY_DETAILS_BEGIN

template<typename _Data>
decltype(auto) storage<_Data>::get(identificator_type ide) const noexcept
{
    return data_.get(ide.value());
}

template<typename _Data>
decltype(auto) storage<_Data>::get(identificator_type ide) noexcept
{
    return data_.get(ide.value());
}

template<typename _Data>
auto storage<_Data>::storage<_Data>::add()
{
    auto current_index = active_;
    data_.resize(++active_);
    return make_identificator(current_index, storage_identificator);
}

template<typename _Data>
auto storage<_Data>::size() const noexcept
{
    return data_.size();
}

template<typename _Buffer>
template<typename _Config>
auto storage_data_maker<_Buffer>::make(const _Config & config) const noexcept
{
    return _Buffer{}.make_buffer(config);
}

template<typename _Maker>
template<typename _Config>
inline auto storage_maker<_Maker>::make(const _Config & config) const noexcept
{
    using data_type = decltype(std::declval<_Maker>().make(config));
    return storage<data_type>{};
}

DES_ENTITY_DETAILS_END
