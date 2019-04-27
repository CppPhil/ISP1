/*!
 * \file expand.hpp
 * \brief Exports a function template to expand a node in a graph.
 **/
#pragma once
#include <edges_of.hpp>             // isp1::edges_of
#include <graph_t.hpp>              // isp1::graph_t
#include <identifier_with_cost.hpp> // isp1::identifier_with_cost
#include <vector>                   // std::vector

namespace isp1 {
/*!
 * \brief Expands a given node.
 * \param node_to_expand The object that identifies the node to be expanded.
 * \param graph The graph that contains the node to be expanded.
 * \tparam NodeIdentifier The type of the object that identifies the node to
 *                        expand.
 * \tparam CostType Type to represent the g costs in the graph.
 * \tparam Nat The kind of graph (directed / undirected).
 * \return The child nodes of node_to_expand along with their g values.
 **/
template<typename NodeIdentifier, typename CostType, Nature Nat>
std::vector<identifier_with_cost<NodeIdentifier>> expand(
    NodeIdentifier                                node_to_expand,
    const graph_t<NodeIdentifier, CostType, Nat>& graph)
{
    // Get the edges. The edges hold the g values in the graph.
    const std::vector<
        typename graph_t<NodeIdentifier, CostType, Nat>::node::edge>
        edges = edges_of(node_to_expand, graph);

    std::vector<identifier_with_cost<NodeIdentifier>> result;

    // Iterate over the edges.
    for (const typename graph_t<NodeIdentifier, CostType, Nat>::node::edge&
             edge : edges) {
        // Get the iterator to the target
        const typename graph_t<NodeIdentifier, CostType, Nat>::const_iterator
            target
            = edge.target();

        // The target iterator is actually an iterator over an internal map of
        // the graph object. Such a map is actually made up of pairs. The .first
        // member will be the identifier of the node saved in the graph in this
        // case. And the .second member will be a shared_ptr to the underlying
        // node object.
        // For documentation of pair see:
        // https://en.cppreference.com/w/cpp/utility/pair

        // Get the node identifier.
        const NodeIdentifier target_node_identifier = target->first;

        // Put that with the cost into the result.
        result.emplace_back(target_node_identifier, edge.cost());
    }

    return result;
}
} // namespace isp1