#pragma once
#include <identifier_with_cost.hpp> // identifier_with_cost
#include <namespaces.hpp>
#include <undirected_graph.hpp> // undirected_graph
#include <vector>               // vector

template<typename NodeIdentifier>
vector<identifier_with_cost<NodeIdentifier>> expand(
    NodeIdentifier                          node_to_expand,
    const undirected_graph<NodeIdentifier>& graph)
{
    const vector<typename undirected_graph<NodeIdentifier>::node::edge> edges
        = graph.get_edges(node_to_expand);

    vector<identifier_with_cost<NodeIdentifier>> result;

    for (const typename undirected_graph<NodeIdentifier>::node::edge& edge :
         edges) {
        const typename undirected_graph<NodeIdentifier>::const_iterator target
            = edge.target();
        const NodeIdentifier target_node_identifier = target->first;

        result.emplace_back(target_node_identifier, edge.cost());
    }

    return result;
}
