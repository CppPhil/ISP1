/*!
 * \file a_star.hpp
 * \brief Exports the a_star function template.
 **/
#pragma once
#include <expand.hpp>             // expand
#include <generate_new_paths.hpp> // generate_new_paths
#include <insert.hpp>             // insert
#include <namespaces.hpp>

/*!
 * \brief The A* algorithm.
 * \param graph The graph to search in.
 * \param start The identifier of the node to start at.
 * \param is_goal A callable that determines whether a given NodeIdentifier
 *                identifies a goal node.
 * \param heuristic A callable that supplies a heuristic
 *                  value (h) for a given NodeIdentifier.
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
    NodeIdentifier                                start,
    IsGoal                                        is_goal,
    Heuristic                                     heuristic)
{
    // The open list. Contains paths of which the last node isn't yet expanded.
    // This list must always remain sorted by the f values of the paths (f = g +
    // h) in ascending order.
    vector<path<NodeIdentifier>> open_list({path<NodeIdentifier>(
        {identifier_with_cost<NodeIdentifier>(start, cost())})});

    // As long as we have paths to explore
    while (not open_list.empty()) {
        // Grab the lowest f path.
        const path<NodeIdentifier> current_path = open_list.front();

        // Delete it from the open list.
        open_list.erase(open_list.begin());

        const NodeIdentifier last_node_of_path
            = current_path.back().node_identifier();

        // If the goal is reached -> we have the path to the goal.
        if (is_goal(last_node_of_path)) { return current_path; }

        // Get all the children of the node with their associated g values
        const vector<identifier_with_cost<NodeIdentifier>> children
            = expand(last_node_of_path, graph);

        // Generate new paths with the children.
        // For each child the current path is taken and the current child is
        // appended to it.
        const vector<path<NodeIdentifier>> new_paths
            = generate_new_paths(current_path, children);

        // Insert the paths just generated into the open list in such a
        // manner so that it remains sorted by the f values of the paths (in
        // ascending order)
        for (const path<NodeIdentifier>& path : new_paths) {
            insert(heuristic, open_list, path);
        }
    }

    // If the open list is empty but we still haven't found a solution
    // -> there is no solution.
    // -> return the empty path.
    return path<NodeIdentifier>();
}
