#pragma once
#include <contains.hpp>           // contains
#include <expand.hpp>             // expand
#include <generate_new_paths.hpp> // generate_new_paths
#include <insert.hpp>             // insert
#include <namespaces.hpp>

template<typename NodeIdentifier, typename IsGoal, typename Heuristic>
path<NodeIdentifier> a_star(
    const undirected_graph<NodeIdentifier>& graph,
    NodeIdentifier                          start,
    IsGoal                                  is_goal,
    Heuristic                               heuristic)
{
    vector<NodeIdentifier> closed_list;

    vector<path<NodeIdentifier>> open_list({path<NodeIdentifier>(
        {identifier_with_cost<NodeIdentifier>(start, cost())})});

    while (not open_list.empty()) {
        const path<NodeIdentifier> current_path = open_list.front();
        open_list.erase(open_list.begin());

        if (not contains(closed_list, current_path.back().node_identifier())) {
            const NodeIdentifier last_node_of_path
                = current_path.back().node_identifier();

            closed_list.push_back(last_node_of_path);

            if (is_goal(last_node_of_path)) { return current_path; }

            const vector<identifier_with_cost<NodeIdentifier>> children
                = expand(last_node_of_path, graph);

            const vector<path<NodeIdentifier>> new_paths
                = generate_new_paths(current_path, children);

            for (const path<NodeIdentifier>& path : new_paths) {
                insert(heuristic, open_list, path);
            }
        }
    }

    return path<NodeIdentifier>();
}
