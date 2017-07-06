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

#ifndef __DES_ENTITY_DETAILS_H_INCLUDED__
#define __DES_ENTITY_DETAILS_H_INCLUDED__

#include <utility>

DES_ENTITY_DETAILS_BEGIN

template<typename _Index>
struct entity
{
    template<typename _Component>
    void register_component(_Component && component) noexcept
    {
        index_.set(std::forward<_Component>(component), 0);
    }

    template<typename _Component>
    void unregister_component(_Component && component) noexcept
    {
        index_.reset(std::forward<_Component>(component));
    }

    template<typename _Component>
    auto test_component(_Component && component) const noexcept
    {
        return index_.test(std::forward<_Component>(component));
    }

    void reset() noexcept
    {
        index_.reset();
    }

    const auto & index() const noexcept { return index_; }

private:

    _Index index_;
};

DES_ENTITY_DETAILS_END

#endif // __DES_ENTITY_DETAILS_H_INCLUDED__
