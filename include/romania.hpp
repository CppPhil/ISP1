/*!
 * \file romania.hpp
 * \brief Exports utilities to work with the romania example.
 **/
#pragma once
#include <cstdint>     // std::uint64_t
#include <graph_t.hpp> // isp1::graph_t
#include <romanian_city.hpp> // isp1::romanian_city

namespace isp1{
/*!
 * \brief Creates a graph of the map of Romania.
 * \return The resulting graph.
 **/
graph_t<romanian_city, cost, UNDIRECTED> create_romania_map();

/*!
 * \brief Returns the heuristic distance (h) for the given city
 *        to the goal city (Bucharest).
 * \return The h value for city.
 **/
std::uint64_t romania_heuristic(romanian_city city);

/*!
 * \brief Constant for the goal_city (Bucharest).
 **/
const romanian_city goal_city = romanian_city::Bucharest;
} // namespace isp1