#pragma once
#include <graph_t.hpp> // graph_t
#include <stdexcept>   // logic_error

/*!
 * \brief Fetches the edges of a given node.
 * \param node The object that identifies the node to get the edges of.
 * \param graph The graph that contains the node in question.
 * \tparam NodeIdentifier The type of the object used to identify nodes.
 * \tparam CostType The type used for the g cost values within the graph.
 * \tparam Nat The nature of the graph (directed / undirected)
 * \return A vector containing the edges of the node given.
 * \throws logic_error if the nature of the graph was not valid.
 **/
template<typename NodeIdentifier, typename CostType, Nature Nat>
vector<typename graph_t<NodeIdentifier, CostType, Nat>::node::edge> edges_of(
    NodeIdentifier                                node,
    const graph_t<NodeIdentifier, CostType, Nat>& graph)
{
    // Compile time branches to handle directed and undirected graphs.
    // This way the compiler will only attempt to compile the branches
    // that would actually compile.

    // Nodes within directed graphs have 'out_edges'.
    if constexpr (Nat == DIRECTED) { return graph.get_out_edges(node); }
    else if constexpr (Nat == UNDIRECTED) { // Undirected case.
        return graph.get_edges(node);
    }
    else { // Sanity check.
        throw logic_error("Invalid nature of graph in edges_of!");
    }
}
