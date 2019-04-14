#pragma once
#include <namespaces.hpp>
#include <path.hpp>                      // path
#include <pl/algo/ranged_algorithms.hpp> // lower_bound
#include <vector>                        // vector

template<typename Heuristic, typename NodeIdentifier>
void insert(
    Heuristic                     heuristic,
    vector<path<NodeIdentifier>>& open_list,
    path<NodeIdentifier>          path_to_insert)
{
    const typename vector<path<NodeIdentifier>>::const_iterator insertion_point
        = lower_bound(
            open_list,
            path_to_insert,
            [&heuristic](
                const path<NodeIdentifier>& lhs,
                const path<NodeIdentifier>& rhs) {
                return (lhs.g() + heuristic(lhs.back().node_identifier()))
                       < (rhs.g() + heuristic(rhs.back().node_identifier()));
            });

    open_list.insert(insertion_point, path_to_insert);
}
