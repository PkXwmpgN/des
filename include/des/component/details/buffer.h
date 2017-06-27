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

#ifndef __DES_COMPONENT_DETAILS_BUFFER_H_INCLUDED__
#define __DES_COMPONENT_DETAILS_BUFFER_H_INCLUDED__

#include <array>
#include <vector>

DES_COMPONENT_DETAILS_BEGIN

template<typename _Self, typename _Data>
struct buffer_base
{
public:

    using data_type = _Data;
    using self_type = _Self;

    buffer_base() = default;
    buffer_base(buffer_base &&) = default;
    buffer_base & operator=(buffer_base &&) = default;
    buffer_base(const buffer_base &) = delete;
    buffer_base & operator=(const buffer_base &) = delete;

    template<typename _Component, typename _Id>
    decltype(auto) get(_Component && component, _Id && ide) const noexcept;

    template<typename _Component, typename _Id>
    decltype(auto) get(_Component && component, _Id && ide) noexcept;

    auto size() const noexcept;

    template<typename _Component>
    constexpr auto contains(_Component && component) const noexcept;

private:

    decltype(auto) self() const noexcept;
    decltype(auto) self() noexcept;
};

template<typename _Data, typename _Capacity>
struct buffer_fixed final :
    buffer_base<buffer_fixed<_Data, _Capacity>, _Data>
{
    using base_type = buffer_base<buffer_fixed<_Data, _Capacity>, _Data>;
    friend base_type;

private:

    const auto & data() const noexcept { return data_; }
    auto & data() noexcept { return data_; }

private:

    std::array<_Data, _Capacity::value> data_;
};

template<typename _Data, typename _Capacity>
struct buffer_dynamic final :
    buffer_base<buffer_dynamic<_Data, _Capacity>, _Data>
{
    using base_type = buffer_base<buffer_fixed<_Data, _Capacity>, _Data>;
    friend base_type;

public:

    buffer_dynamic();

private:

    const auto & data() const noexcept { return data_; }
    auto data() noexcept { return data_; }

private:

    std::vector<_Data> data_;
};

template<typename... _Components>
struct data_maker
{
    template<typename _Config>
    constexpr auto make(const _Config & cfg) const noexcept;
};

template<typename _Maker>
struct buffer_maker
{
    template<typename _Config>
    constexpr auto make(const _Config & cfg) const noexcept;
};

DES_COMPONENT_DETAILS_END

#endif // __DES_COMPONENT_DETAILS_BUFFER_H_INCLUDED__
