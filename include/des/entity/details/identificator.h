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

#ifndef __DES_ENTITY_DETAILS_IDENTIFICATOR_H_INCLUDED__
#define __DES_ENTITY_DETAILS_IDENTIFICATOR_H_INCLUDED__

#include <limits>

DES_ENTITY_DETAILS_BEGIN

template<typename _Integral>
constexpr auto invalid_identificator_value = std::numeric_limits<_Integral>::max();

template<typename _Integral, typename _Tag>
struct identificator
{
public:

    using integral_type = _Integral;

    constexpr identificator() noexcept
        : identificator(invalid_identificator_value<integral_type>)
    {}

    constexpr explicit identificator(integral_type value) noexcept
        : id_{value}
    {}

    constexpr auto value() const noexcept { return id_; }

private:

    integral_type id_;
};

template<typename _Integral, typename _Tag>
inline constexpr bool operator == (identificator<_Integral, _Tag> l,
    identificator<_Integral, _Tag> r) noexcept
{
    return l.value() == r.value();
}

template<typename _Integral, typename _Tag>
inline constexpr bool operator != (identificator<_Integral, _Tag> l,
    identificator<_Integral, _Tag> r) noexcept
{
    return !(l == r);
}

template<typename _Integral, typename _Tag>
inline constexpr bool is_valid(identificator<_Integral, _Tag> iid) noexcept
{
    return iid.value() == invalid_identificator_value<_Integral>;
}

template<typename _Integral, typename _Tag>
inline constexpr auto make_identificator(_Integral && value, _Tag &&)
{
    return identificator
    <
        std::decay_t<_Integral>,
        std::decay_t<_Tag>
    >{value};
}

DES_ENTITY_DETAILS_END

#endif // __DES_ENTITY_DETAILS_IDENTIFICATOR_H_INCLUDED__
