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

DES_ENTITY_DETAILS_BEGIN

template<typename _Index>
template<typename _Component, typename _Storage>
inline decltype(auto) entity<_Index>::
    register_component(_Component && component, _Storage && storage)
{
    if(test_component(component))
        return get_component(std::forward<_Component>(component),
                             std::forward<_Storage>(storage));

    auto component_index = storage.add(component);
    index_.set(component, component_index);
    return storage.get(component, component_index);
}

template<typename _Index>
template<typename _Component, typename _Storage>
inline void entity<_Index>::
    unregister_component(_Component && component, _Storage && storage) noexcept
{
    (void)component;
    (void)storage;
}

template<typename _Index>
template<typename _Component, typename _Storage>
inline decltype(auto) entity<_Index>::
    get_component(_Component && component, _Storage && storage) const noexcept
{
    return storage.get(component, index_.get(component));
}

template<typename _Index>
template<typename _Component, typename _Storage>
inline decltype(auto) entity<_Index>::
    get_component(_Component && component, _Storage && storage) noexcept
{
    return storage.get(component, index_.get(component));
}

template<typename _Index>
template<typename _Component>
inline auto entity<_Index>::
    test_component(_Component && component) const noexcept
{
    return index_.test(std::forward<_Component>(component));
}

template<typename _Index>
inline void entity<_Index>::reset() noexcept
{
    index_.reset();
}

DES_ENTITY_DETAILS_END
