/*!
 * \file non_monotonic.hpp
 * \brief Exports functions regarding the non monotonic example.
**/
#pragma once
#include <graph_t.hpp> // graph_t
#include <string>      // string

/*!
 * \brief Creates the graph for the non monotonic heuristic example.
 **/
graph_t<string, cost, DIRECTED> make_non_monotonic_graph();

/*!
 * \brief The non monotonic heuristic.
 * \param node_identifier The node to get the h value of.
 * \return The resulting h value.
 **/
cost non_monotonic_heuristic(string node_identifier);

/*!
 * \brief Constant for the goal node of the non monotonic heuristic example.
 **/
const string non_monotonic_goal_node = "GOAL";
