#ifndef INCG_ISP1_ASTAR_HPP
#define INCG_ISP1_ASTAR_HPP
#include <ciso646>                       // not
#include <iterator>                      // std::begin, std::end
#include <path.hpp>                      // isp1::Path
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find
#include <undirected_graph.hpp>          // isp1::UndirectedGraph
#include <utility>                       // std::move
#include <vector>                        // std::vector

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
    const UndirectedGraph<NodeIdentifier>& graph,
    NodeIdentifier                         start,
    IsGoal                                 isGoal,
    Heuristic                              heuristic)
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
