/*!
 * \file a_star.hpp
 * \brief Exports the a_star function template.
 **/
#pragma once
#include <ciso646>                       // not, or
#include <expand.hpp>                    // isp1::expand
#include <generate_new_paths.hpp>        // isp1::generate_new_paths
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find
#include <vector>                        // std::vector
#include <queue> // std::priority_queue

namespace isp1 {
/*!
 * \brief The A* algorithm.
 * \param graph The graph to search in.
 * \param start_nodes The start nodes.
 * \param is_goal A callable that determines whether a given NodeIdentifier
 *                identifies a goal node.
 * \param heuristic A callable that supplies a heuristic
 *                  value (h) for a given NodeIdentifier.
 * \param use_closed_list Whether to use a closed list or not.
 * \tparam NodeIdentifier The type of the kind of object
 *                        that identifies a node, e.g.
 *                        a string or an enum.
 * \tparam CostType The type used to represent the g cost values in the graph.
 * \tparam Nat The nature of the graph (directed / undirected)
 * \tparam IsGoal The type of the is_goal callable.
 * \tparam Heuristic The type of the heuristic callable.
 * \return The shortest path from the start node to the goal
 *         node (beginning at the start node) or an empty
 *         path if no path could be found.
 *
 * Finds the shortest path from a start node to a goal node in a graph.
 * The search is guided by the heuristic supplied.
 **/
template<
    typename NodeIdentifier,
    typename CostType,
    Nature Nat,
    typename IsGoal,
    typename Heuristic>
path<NodeIdentifier> a_star(
    const graph_t<NodeIdentifier, CostType, Nat>& graph,
    std::vector<NodeIdentifier>                   start_nodes,
    IsGoal                                        is_goal,
    Heuristic                                     heuristic,
    bool                                          use_closed_list = true)
{
    // Contains nodes already visited.
    std::vector<NodeIdentifier> closed_list;

    const auto comparator = [&heuristic](const path<NodeIdentifier>& lhs, const path<NodeIdentifier>& rhs) {
        return (lhs.g() + heuristic(lhs.back().node_identifier()))
               > (rhs.g() + heuristic(rhs.back().node_identifier()));
    };

    // The open list. Contains paths of which the last node isn't yet expanded.
    // This list must always remain sorted by the f values of the paths (f = g +
    // h) in ascending order.
    std::priority_queue<path<NodeIdentifier>, std::vector<path<NodeIdentifier>>, decltype(comparator)> open_list(
        comparator
    );

    for (NodeIdentifier node : start_nodes) {
        open_list.push(path<NodeIdentifier>(
                {identifier_with_cost<NodeIdentifier>(node, cost())}));
    }

    // As long as we have paths to explore
    while (not open_list.empty()) {
        // Grab the lowest f path.
        const path<NodeIdentifier> current_path = open_list.top();

        // Delete it from the open list.
        open_list.pop();

        // Only handle the node if it's not in the closed list
        if ((pl::algo::find(closed_list, current_path.back().node_identifier())
             == closed_list.end())
            or not use_closed_list) {
            const NodeIdentifier last_node_of_path
                = current_path.back().node_identifier();
            closed_list.push_back(last_node_of_path);

            // If the goal is reached -> we have the path to the goal.
            if (is_goal(last_node_of_path)) { return current_path; }

            // Get all the children of the node with their associated g values
            const std::vector<identifier_with_cost<NodeIdentifier>> children
                = expand(last_node_of_path, graph);

            // Generate new paths with the children.
            // For each child the current path is taken and the current child is
            // appended to it.
            const std::vector<path<NodeIdentifier>> new_paths
                = generate_new_paths(current_path, children);

            // Insert the paths just generated into the open list in such a
            // manner so that it remains sorted by the f values of the paths (in
            // ascending order)
            for (const path<NodeIdentifier>& path : new_paths) {
                open_list.push(path);
            }
        }
    }

    // If the open list is empty but we still haven't found a solution
    // -> there is no solution.
    // -> return the empty path.
    return path<NodeIdentifier>();
}
} // namespace isp1
