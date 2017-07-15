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

#include "des/meta/options.h"

DES_SYSTEM_DETAILS_BEGIN

namespace /* anonymous */
{
    namespace keys
    {
        constexpr auto system = meta::options::key_v<0>;
        constexpr auto input = meta::options::key_v<1>;
        constexpr auto output = meta::options::key_v<2>;
        constexpr auto dependencies = meta::options::key_v<3>;
    }
}

template<typename _Data>
template<typename... _Input>
inline constexpr auto node<_Data>::
    input(_Input && ... input) const noexcept
{
    using type = decltype(meta::options::set(data_, keys::input,
        std::make_tuple(std::forward<_Input>(input)...)));
    return node<type>{};
}

template<typename _Data>
template<typename... _Output>
inline constexpr auto node<_Data>::
    output(_Output && ... output) const noexcept
{
    using type = decltype(meta::options::set(data_, keys::output,
        std::make_tuple(std::forward<_Output>(output)...)));
    return node<type>{};
}

template<typename _Data>
template<typename... _Dependencies>
inline constexpr auto node<_Data>::
    dependencies(_Dependencies && ... dependencies) const noexcept
{
    using type = decltype(meta::options::set(data_, keys::dependencies,
        std::make_tuple(std::forward<_Dependencies>(dependencies)...)));
    return node<type>{};
}

template<typename _Data>
inline constexpr auto node<_Data>::system() const noexcept
{
    using result = decltype(meta::options::get(data_, keys::system));
    return result{};
}

template<typename _Data>
inline constexpr auto node<_Data>::input_list() const noexcept
{
    using result = decltype(meta::options::get(data_, keys::input));
    return result{};
}

template<typename _Data>
inline constexpr auto node<_Data>::output_list() const noexcept
{
    using result = decltype(meta::options::get(data_, keys::output));
    return result{};
}

template<typename _Data>
inline constexpr auto node<_Data>::dependency_list() const noexcept
{
    using result = decltype(meta::options::get(data_, keys::dependencies));
    return result{};
}

template<typename _System>
inline constexpr auto make_node(_System && system) noexcept
{
    using type  = decltype(meta::options::set(meta::options::empty_v, keys::system, system));
    using type1 = decltype(meta::options::set(type{}, keys::input, std::make_tuple()));
    using type2 = decltype(meta::options::set(type1{}, keys::output, std::make_tuple()));
    using type3 = decltype(meta::options::set(type2{}, keys::dependencies, std::make_tuple()));
    return node<type3>{};
}

DES_SYSTEM_DETAILS_END
