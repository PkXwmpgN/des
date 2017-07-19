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

#ifndef __DES_CORE_DETAILS_BUFFER_H_INCLUDED__
#define __DES_CORE_DETAILS_BUFFER_H_INCLUDED__

#include <array>
#include <vector>

DES_CORE_DETAILS_BEGIN

template<typename _Data, typename _Capacity>
struct buffer_fixed
{
    using value_type = _Data;
    using data_type = std::array<value_type, _Capacity::value>;
    using index_type = typename data_type::size_type;

    buffer_fixed() = default;
    buffer_fixed(buffer_fixed &&) = default;
    buffer_fixed & operator=(buffer_fixed &&) = default;
    buffer_fixed(const buffer_fixed &) = delete;
    buffer_fixed & operator=(const buffer_fixed &) = delete;

    decltype(auto) get(index_type value) const noexcept;
    decltype(auto) get(index_type value) noexcept;

    auto size() const noexcept;
    void resize(index_type value);

private:

    data_type data_;
};

template<typename _Data, typename _Capacity>
struct buffer_dynamic
{
    using value_type = _Data;
    using data_type = std::vector<value_type>;
    using index_type = typename data_type::size_type;

    buffer_dynamic() = default;
    buffer_dynamic(buffer_dynamic &&) = default;
    buffer_dynamic & operator=(buffer_dynamic &&) = default;
    buffer_dynamic(const buffer_dynamic &) = delete;
    buffer_dynamic & operator=(const buffer_dynamic &) = delete;

    decltype(auto) get(index_type value) const noexcept;
    decltype(auto) get(index_type value) noexcept;

    auto size() const noexcept;
    void resize(index_type value);

private:

    data_type data_ = data_type(_Capacity::value);
};

template<typename _Maker>
struct buffer_maker
{
    template<typename _Config>
    auto make(const _Config & cfg) const noexcept;
};

DES_CORE_DETAILS_END

#endif // __DES_CORE_DETAILS_BUFFER_H_INCLUDED__
