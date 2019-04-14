#ifndef INCG_ISP1_ASTAR_HPP
#define INCG_ISP1_ASTAR_HPP
#include <ciso646>
#include <functional>
#include <graph.hpp>
#include <iterator>
#include <path.hpp>
#include <pl/algo/ranged_algorithms.hpp>
#include <string>
#include <vector>

namespace isp1 {
#if 0
graph_undirected<std::string, int, int>::search_path aStar(
    const graph_undirected<std::string, int, int>&          graph,
    graph_undirected<std::string, int, int>::const_iterator start,
    std::function<bool(graph_undirected<std::string, int, int>::const_iterator)>
                                                                  isGoal,
    std::function<graph_undirected<std::string, int, int>::cost_type(
        graph_undirected<std::string, int, int>::const_iterator)> heuristic);
#endif

template<typename NodeIdentifier>
std::vector<IdentifierWithCost<NodeIdentifier>> expand(
    NodeIdentifier                                     nodeToExpand,
    const graph_undirected<NodeIdentifier, int, Cost>& graph)
{
    std::vector<
        typename graph_undirected<NodeIdentifier, int, Cost>::node::edge>
        edges{graph.get_edges(nodeToExpand)};

    std::vector<IdentifierWithCost<NodeIdentifier>> result{};

    for (const typename graph_undirected<NodeIdentifier, int, Cost>::node::edge&
             edge : edges) {
        typename graph_undirected<NodeIdentifier, int, Cost>::const_iterator
                              target{edge.target()};
        const NodeIdentifier& targetNodeIdentifier{target->first};

        result.emplace_back(targetNodeIdentifier, edge.cost());
    }

    return result;
}

template<typename NodeIdentifier>
std::vector<Path<NodeIdentifier>> generateNewPaths(
    const Path<NodeIdentifier>&                            oldPath,
    const std::vector<IdentifierWithCost<NodeIdentifier>>& children)
{
    std::vector<Path<NodeIdentifier>> result{};

    for (const IdentifierWithCost<NodeIdentifier>& child : children) {
        Path<NodeIdentifier> copy{oldPath};
        copy.append(child);
        result.push_back(std::move(copy));
    }

    return result;
}

template<typename Heuristic, typename NodeIdentifier>
void insert(
    Heuristic                          heuristic,
    std::vector<Path<NodeIdentifier>>& openList,
    Path<NodeIdentifier>               pathToInsert)
{
    typename std::vector<Path<NodeIdentifier>>::iterator insertionPoint{
        pl::algo::lower_bound(
            openList,
            pathToInsert,
            [&heuristic](
                const Path<NodeIdentifier>& lhs,
                const Path<NodeIdentifier>& rhs) {
                return (lhs.g() + heuristic(lhs.back().nodeIdentifier))
                       < (rhs.g() + heuristic(rhs.back().nodeIdentifier));
            })};

    openList.insert(insertionPoint, std::move(pathToInsert));
}

template<typename NodeIdentifier, typename IsGoal, typename Heuristic>
Path<NodeIdentifier> aStar(
    const graph_undirected<NodeIdentifier, int, Cost>& graph,
    NodeIdentifier                                     start,
    IsGoal                                             isGoal,
    Heuristic                                          heuristic)
{
    using SearchPath = Path<NodeIdentifier>;

    std::vector<NodeIdentifier> closedList{};

    std::vector<SearchPath> openList{
        SearchPath{IdentifierWithCost<NodeIdentifier>{start, Cost{}}}};

    while (not openList.empty()) {
        SearchPath p{openList.front()};
        openList.erase(std::begin(openList));

        // TODO: prettify
        // If it's not in the closed list.
        if (pl::algo::find(closedList, p.back().nodeIdentifier)
            == std::end(closedList)) {
            NodeIdentifier last{p.back().nodeIdentifier};

            closedList.push_back(last);

            if (isGoal(last)) { return p; }

            const std::vector<IdentifierWithCost<NodeIdentifier>> children{
                expand(last, graph)};

            const std::vector<SearchPath> newPaths{
                generateNewPaths(p, children)};

            for (const SearchPath& path : newPaths) {
                insert(heuristic, openList, path);
            }
        }
    }

    return SearchPath{};
}
} // namespace isp1
#endif // INCG_ISP1_ASTAR_HPP
