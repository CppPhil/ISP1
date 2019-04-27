#pragma once
#include <graph_t.hpp> // isp1::graph_t
#include <stdexcept>   // std::logic_error

namespace isp1 {
/*!
 * \brief Implementation function template to get the edges of a node in
 *        a directed graph.
 * \param node The node to get the outgoing edges of.
 * \param graph The graph that contains the node.
 * \tparam NodeIdentifier The type used to identify a node.
 * \tparam CostType The cost type for the g values in the graph.
 * \return A vector containing the outgoing edges of the node given.
 **/
template<typename NodeIdentifier, typename CostType>
std::vector<typename graph_t<NodeIdentifier, CostType, DIRECTED>::node::edge>
edges_of_impl(
    NodeIdentifier                                     node,
    const graph_t<NodeIdentifier, CostType, DIRECTED>& graph)
{
    return graph.get_out_edges(node);
}

/*!
 * \brief Implementation function template to get the edges of a node in
 *        an undirected graph.
 * \param node The node to get the edges of.
 * \param graph The graph that contains the node.
 * \tparam NodeIdentifier The type used to identify a node.
 * \tparam CostType The cost type for the g values in the graph.
 * \return A vector containing the edges of the node given.
 **/
template<typename NodeIdentifier, typename CostType>
std::vector<typename graph_t<NodeIdentifier, CostType, UNDIRECTED>::node::edge>
edges_of_impl(
    NodeIdentifier                                       node,
    const graph_t<NodeIdentifier, CostType, UNDIRECTED>& graph)
{
    return graph.get_edges(node);
}

/*!
 * \brief Fetches the edges of a given node.
 * \param node The object that identifies the node to get the edges of.
 * \param graph The graph that contains the node in question.
 * \tparam NodeIdentifier The type of the object used to identify nodes.
 * \tparam CostType The type used for the g cost values within the graph.
 * \tparam Nat The nature of the graph (directed / undirected)
 * \return A vector containing the edges of the node given.
 **/
template<typename NodeIdentifier, typename CostType, Nature Nat>
std::vector<typename graph_t<NodeIdentifier, CostType, Nat>::node::edge>
edges_of(
    NodeIdentifier                                node,
    const graph_t<NodeIdentifier, CostType, Nat>& graph)
{
    return edges_of_impl(node, graph);
}
} // namespace isp1