#pragma once
#include <namespaces.hpp>
#include <path.hpp>                      // Path
#include <pl/algo/ranged_algorithms.hpp> // lower_bound
#include <vector>                        // vector

template<typename Heuristic, typename NodeIdentifier>
void insert(
    Heuristic                     heuristic,
    vector<Path<NodeIdentifier>>& openList,
    Path<NodeIdentifier>          pathToInsert)
{
    typename vector<Path<NodeIdentifier>>::iterator insertionPoint
        = lower_bound(
            openList,
            pathToInsert,
            [&heuristic](
                const Path<NodeIdentifier>& lhs,
                const Path<NodeIdentifier>& rhs) {
                return (lhs.g() + heuristic(lhs.back().nodeIdentifier()))
                       < (rhs.g() + heuristic(rhs.back().nodeIdentifier()));
            });

    openList.insert(insertionPoint, pathToInsert);
}
