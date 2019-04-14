#ifndef INCG_ISP1_EXPAND_HPP
#define INCG_ISP1_EXPAND_HPP
#include <identifier_with_cost.hpp> // isp1::IdentifierWithCost
#include <undirected_graph.hpp>     // isp1::UndirectedGraph
#include <vector>                   // std::vector

namespace isp1 {
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
} // namespace isp1
#endif // INCG_ISP1_EXPAND_HPP