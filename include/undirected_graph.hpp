#ifndef INCG_ISP1_UNDIRECTED_GRAPH_HPP
#define INCG_ISP1_UNDIRECTED_GRAPH_HPP
#include <cost.hpp>  // isp1::Cost
#include <graph.hpp> // graph_undirected

namespace isp1 {
template<typename NodeIdentifier, typename CostType = Cost>
using UndirectedGraph = graph_undirected<
    /* key_type */ NodeIdentifier,
    /* graphed_type (no idea what this is, doesn't seem like it's used anywhere)
     */
    int,
    /* cost_type */ CostType>;
} // namespace isp1
#endif // INCG_ISP1_UNDIRECTED_GRAPH_HPP
