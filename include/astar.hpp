#ifndef INCG_ISP1_ASTAR_HPP
#define INCG_ISP1_ASTAR_HPP
#include <functional>
#include <graph.hpp>
#include <string>

namespace isp1 {
graph_undirected<std::string, int, int>::search_path aStar(
    const graph_undirected<std::string, int, int>&          graph,
    graph_undirected<std::string, int, int>::const_iterator start,
    std::function<bool(graph_undirected<std::string, int, int>::const_iterator)>
                                                                  isGoal,
    std::function<graph_undirected<std::string, int, int>::cost_type(
        graph_undirected<std::string, int, int>::const_iterator)> heuristic);
} // namespace isp1
#endif // INCG_ISP1_ASTAR_HPP
