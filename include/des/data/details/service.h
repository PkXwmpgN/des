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

#ifndef __DES_DATA_DETAILS_SERVICE_H_INCLUDED__
#define __DES_DATA_DETAILS_SERVICE_H_INCLUDED__

DES_DATA_DETAILS_BEGIN

template<typename _Components, typename _Entities>
struct service
{
public:

    using component_storage_type = _Components;
    using entity_storage_type = _Entities;

    auto create_entity();

    template<typename _Id>
    auto destroy_entity(_Id && id);

    template<typename _Component, typename _Id>
    decltype(auto) add_component(_Component && component, _Id && id);

    template<typename _Component, typename _Id>
    decltype(auto) get_component(_Component && component, _Id && id) noexcept;

    template<typename _Component, typename _Id>
    decltype(auto) get_component(_Component && component, _Id && id) const noexcept;

    template<typename _Component, typename _Id>
    void remove_component(_Component && component, _Id && id);

    template<typename _Component, typename _Id>
    auto test_component(_Component && component, _Id && id) const noexcept;

    template<typename _Id>
    auto test_entity(_Id && id) const noexcept;

    auto size() const noexcept;

private:

    component_storage_type components_;
    entity_storage_type entities_;
};

template<typename _Storage>
struct service_maker
{
    template<typename _Config>
    auto make(const _Config & config) const noexcept;
};

template<typename _Storage>
constexpr auto make_service(_Storage && storage) noexcept;

DES_DATA_DETAILS_END

#endif // __DES_DATA_DETAILS_SERVICE_H_INCLUDED__
