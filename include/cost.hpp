/*!
 * \file cost.hpp
 * \brief Exports the type used for costs.
 **/
#pragma once
#include <cstdint> // std::uint64_t

namespace isp1 {
/*!
 * \brief The cost type is defined as a 64 bit unsigned integer type.
 *        This is the largest integer type natively supported by common
 *        desktop processors.
 *        Using a signed integer type wouldn't make sense as negative
 *        cost values are not permissable for the A* algorithm much like
 *        for Dijkstra's algorithm.
 **/
typedef std::uint64_t cost;
} // namespace isp1