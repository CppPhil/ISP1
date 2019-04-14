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
    vector<NodeIdentifier> closedList;

    vector<Path<NodeIdentifier>> openList({Path<NodeIdentifier>(
        {IdentifierWithCost<NodeIdentifier>(start, Cost())})});

    while (not openList.empty()) {
        Path<NodeIdentifier> currentPath = openList.front();
        openList.erase(openList.begin());

        if (not contains(closedList, currentPath.back().nodeIdentifier())) {
            NodeIdentifier lastNodeOfPath = currentPath.back().nodeIdentifier();

            closedList.push_back(lastNodeOfPath);

            if (isGoal(lastNodeOfPath)) { return currentPath; }

            const vector<IdentifierWithCost<NodeIdentifier>> children
                = expand(lastNodeOfPath, graph);

            const vector<Path<NodeIdentifier>> newPaths
                = generateNewPaths(currentPath, children);

            for (const Path<NodeIdentifier>& path : newPaths) {
                insert(heuristic, openList, path);
            }
        }
    }

    return Path<NodeIdentifier>();
}
