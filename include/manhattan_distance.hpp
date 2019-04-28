/*!
 * \file manhattan_distance.hpp
 * \brief Exports the manhattan_distance function.
 **/
#pragma once
#include <cstdint>      // std::uint64_t
#include <position.hpp> // isp1::position

namespace isp1 {
/*!
 * \brief Calculates the manhattan distance between two positions.
 * \param pos1 The first position.
 * \param pos2 The second position.
 * \return The resulting manhattan distance.
 **/
std::uint64_t manhattan_distance(position pos1, position pos2);
} // namespace isp1