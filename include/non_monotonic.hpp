/*!
 * \file non_monotonic.hpp
 * \brief Exports functions regarding the non monotonic example.
 **/
#pragma once
#include <graph_t.hpp> // isp1::graph_t
#include <string>      // std::string

namespace isp1{
/*!
 * \brief Creates the graph for the non monotonic heuristic example.
 **/
graph_t<std::string, cost, DIRECTED> make_non_monotonic_graph();

/*!
 * \brief The non monotonic heuristic.
 * \param node_identifier The node to get the h value of.
 * \return The resulting h value.
 **/
cost non_monotonic_heuristic(std::string node_identifier);

/*!
 * \brief Constant for the goal node of the non monotonic heuristic example.
 **/
const std::string non_monotonic_goal_node = "GOAL";
} // namespace isp1