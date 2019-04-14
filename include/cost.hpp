/*!
 * \file cost.hpp
 * \brief Exports the type used for costs.
 **/
#pragma once
#include <cstdint> // uint64_t
#include <namespaces.hpp>

/*!
 * \brief The cost type is defined as a 64 bit unsigned integer type.
 *        This is the largest integer type natively supported by common
 *        desktop processors.
 *        Using a signed integer type wouldn't make sense as negative
 *        cost values are not permissable for the A* algorithm much like
 *        for Dijkstra's algorithm.
 **/
typedef uint64_t cost;
