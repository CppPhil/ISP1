#ifndef INCG_ISP1_ASTAR_HPP
#define INCG_ISP1_ASTAR_HPP
#include <contains.hpp>           // isp1::contains
#include <expand.hpp>             // isp1::expand
#include <generate_new_paths.hpp> // isp1::generateNewPaths
#include <insert.hpp>             // isp1::insert

namespace isp1 {
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

        if (not contains(closedList, p.back().nodeIdentifier())) {
            NodeIdentifier last{p.back().nodeIdentifier()};

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
