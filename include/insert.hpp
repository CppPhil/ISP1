#pragma once
#include <path.hpp>                      // Path
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::lower_bound
#include <vector>                        // std::vector

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
                return (lhs.g() + heuristic(lhs.back().nodeIdentifier()))
                       < (rhs.g() + heuristic(rhs.back().nodeIdentifier()));
            })};

    openList.insert(insertionPoint, std::move(pathToInsert));
}
