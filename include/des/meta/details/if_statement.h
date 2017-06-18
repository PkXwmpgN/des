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

#ifndef __DES_META_DETAILS_IF_STATEMENT_H_INCLUDED__
#define __DES_META_DETAILS_IF_STATEMENT_H_INCLUDED__

DES_META_DETAILS_BEGIN

template<typename _Function>
struct if_statement_result final : _Function
{
    constexpr if_statement_result(_Function && fn) noexcept
        : _Function{std::forward<_Function>(fn)}
    {}

    template<typename _F>
    constexpr auto & then_(_F &&) noexcept
    {
        return *this;
    }

    template<typename _F>
    constexpr auto & else_(_F &&) noexcept
    {
        return *this;
    }
};

template<typename _Function>
constexpr auto make_if_statement_result(_Function && fn) noexcept
{
    return if_statement_result<_Function>{std::forward<_Function>(fn)};
}

template<bool _Result>
struct if_statement;

template<>
struct if_statement<false> final
{
    template<typename _Function>
    constexpr auto & then_(_Function &&) noexcept
    {
        return *this;
    }

    template<typename _Function>
    constexpr auto else_(_Function && fn) noexcept
    {
        return make_if_statement_result(std::forward<_Function>(fn));
    }

    template<typename... Ts>
    constexpr auto operator()(Ts && ...) noexcept
    {}
};

template<>
struct if_statement<true> final
{
    template<typename _Function>
    constexpr auto & else_(_Function &&) noexcept
    {
        return *this;
    }

    template<typename _Function>
    constexpr auto then_(_Function && fn) noexcept
    {
        return make_if_statement_result(std::forward<_Function>(fn));
    }
};

template<typename _Predicate>
inline constexpr auto make_if_statement(_Predicate pred) noexcept
{
    return if_statement<pred>{};
}

DES_META_DETAILS_END

#endif // __DES_META_DETAILS_IF_STATEMENT_H_INCLUDED__
