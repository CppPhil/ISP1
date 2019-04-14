#pragma once
#include <contains.hpp>           // contains
#include <expand.hpp>             // expand
#include <generate_new_paths.hpp> // generateNewPaths
#include <insert.hpp>             // insert
#include <namespaces.hpp>

template<typename NodeIdentifier, typename IsGoal, typename Heuristic>
Path<NodeIdentifier> aStar(
    const UndirectedGraph<NodeIdentifier>& graph,
    NodeIdentifier                         start,
    IsGoal                                 isGoal,
    Heuristic                              heuristic)
{
    using SearchPath = Path<NodeIdentifier>;

    vector<NodeIdentifier> closedList{};

    vector<SearchPath> openList{
        SearchPath{IdentifierWithCost<NodeIdentifier>{start, Cost{}}}};

    while (not openList.empty()) {
        SearchPath p{openList.front()};
        openList.erase(begin(openList));

        if (not contains(closedList, p.back().nodeIdentifier())) {
            NodeIdentifier last{p.back().nodeIdentifier()};

            closedList.push_back(last);

            if (isGoal(last)) { return p; }

            const vector<IdentifierWithCost<NodeIdentifier>> children{
                expand(last, graph)};

            const vector<SearchPath> newPaths{generateNewPaths(p, children)};

            for (const SearchPath& path : newPaths) {
                insert(heuristic, openList, path);
            }
        }
    }

    return SearchPath{};
}
