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

#include <tuple>
#include <utility>
#include "des/meta/traits.h"
#include "des/meta/algorithm.h"

DES_SYSTEM_DETAILS_BEGIN

namespace /* anonymous */
{
    template<typename _Discovered>
    inline auto filter_(std::tuple<> &&, _Discovered &&)
    {
        return std::make_tuple();
    }

    template<typename _Node, typename... _Nodes, typename _Discovered>
    inline auto filter_(std::tuple<_Node, _Nodes...> &&, _Discovered && discovered)
    {
        auto node = meta::if_(meta::is_tuple_contains<_Node, _Discovered>{})
            .then_([](){ return std::make_tuple(); })
            .else_([](){ return std::make_tuple(_Node{}); })();

        auto step = std::tuple_cat(std::make_tuple(_Node{}),
            std::forward<_Discovered>(discovered));

        return std::tuple_cat(node, filter_(std::make_tuple(_Nodes{}...), step));
    }

    template<typename _Node, typename... _Nodes>
    inline auto filter(std::tuple<_Node, _Nodes...> && tuple)
    {
        return filter_(std::forward<std::tuple<_Node, _Nodes...>>(tuple),
            std::make_tuple());
    }

    template<typename _Node>
    inline auto dfs(_Node && node)
    {
        auto list = meta::cat(node.dependency_list(),
            [](auto && node) { return dfs(node); });
        return std::tuple_cat(list, std::make_tuple(node));
    }

    template<typename _Nodes>
    inline auto sort(_Nodes && nodes)
    {
        return filter(meta::cat(nodes,
                [](auto && node) { return dfs(node); }));
    }
}

template<typename ... _Nodes>
inline constexpr auto make_sequence(_Nodes && ... nodes)
{
    using type = decltype(sort(std::make_tuple(std::forward<_Nodes>(nodes)...)));
    return type{};
}

DES_SYSTEM_DETAILS_END
