#pragma once
#include <identifier_with_cost.hpp> // IdentifierWithCost
#include <undirected_graph.hpp>     // UndirectedGraph
#include <vector>                   // std::vector

template<typename NodeIdentifier>
std::vector<IdentifierWithCost<NodeIdentifier>> expand(
    NodeIdentifier                         nodeToExpand,
    const UndirectedGraph<NodeIdentifier>& graph)
{
    std::vector<typename UndirectedGraph<NodeIdentifier>::node::edge> edges{
        graph.get_edges(nodeToExpand)};

    std::vector<IdentifierWithCost<NodeIdentifier>> result{};

    for (const typename UndirectedGraph<NodeIdentifier>::node::edge& edge :
         edges) {
        typename UndirectedGraph<NodeIdentifier>::const_iterator target{
            edge.target()};
        const NodeIdentifier& targetNodeIdentifier{target->first};

        result.emplace_back(targetNodeIdentifier, edge.cost());
    }

    return result;
}
