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

DES_DATA_DETAILS_BEGIN

template<typename _Components, typename _Entities>
inline auto service<_Components, _Entities>::create_entity()
{
    return entities_.add();
}

template<typename _Components, typename _Entities>
template<typename _Id>
inline auto service<_Components, _Entities>::destroy_entity(_Id && id)
{
    (void)id;
}

template<typename _Components, typename _Entities>
template<typename _Component, typename _Id>
inline decltype(auto) service<_Components, _Entities>::
    add_component(_Component && component, _Id && id)
{
    assert(test_entity(id));

    decltype(auto) entity = entities_.get(id);
    if(entity.test_component(component))
        return entity.get_component(component, components_);

    entity.get_component_index(component) = components_.add(component);
    entity.get_component_meta(component, components_).owner(id.value());
    return entity.get_component(component, components_);
}

template<typename _Components, typename _Entities>
template<typename _Component, typename _Id>
inline decltype(auto) service<_Components, _Entities>::
    get_component(_Component && component, _Id && id) noexcept
{
    assert(test_entity(id));
    return entities_.get(id).get_component(component, components_);
}

template<typename _Components, typename _Entities>
template<typename _Component, typename _Id>
inline decltype(auto) service<_Components, _Entities>::
    get_component(_Component && component, _Id && id) const noexcept
{
    assert(test_entity(id));
    return entities_.get(id).get_component(component, components_);
}

template<typename _Components, typename _Entities>
template<typename _Component, typename _Id>
inline void service<_Components, _Entities>::
    remove_component(_Component && component, _Id && id)
{
    assert(test_entity(id));

    decltype(auto) entity = entities_.get(id);
    auto index = entity.get_component_index(component);
    entity.reset_component_index(component);
    if(components_.remove(component, index))
    {
        auto owner = components_.meta(component, index).owner();
        auto identificator = typename _Entities::identificator_type{owner};
        entities_.get(identificator).get_component_index(component) = index;
    }
}

template<typename _Components, typename _Entities>
template<typename _Component, typename _Id>
inline auto service<_Components, _Entities>::
    test_component(_Component && component, _Id && id) const noexcept
{
    assert(test_entity(id));
    return entities_.get(id).test_component(component);
}

template<typename _Components, typename _Entities>
template<typename _Id>
inline auto service<_Components, _Entities>::test_entity(_Id && id) const noexcept
{
    return id.value() < entities_.size();
}

template<typename _Storage>
template<typename _Config>
inline auto service_maker<_Storage>::make(const _Config & config) const noexcept
{
    return service
    <
        decltype(std::declval<_Storage>().components().make(config)),
        decltype(std::declval<_Storage>().entities().make(config))
    >{};
}

template<typename _Storage>
inline constexpr auto make_service(_Storage &&) noexcept
{
    return service_maker<std::decay_t<_Storage>>{};
}

DES_DATA_DETAILS_END
