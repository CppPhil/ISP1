/*!
 * \file graph_t.hpp
 * \brief Exports the graph_t alias template.
 **/
#pragma once
#include <cost.hpp>  // cost
#include <graph.hpp> // graph, Nature

/*!
 * \brief Type used to represent a graph.
 * \tparam NodeIdentifier The type that is used to uniquely identify the nodes
 *                        in the graph.
 * \tparam GraphedType No clue what this actually is, seems to be
 *                     stored with the nodes somehow or something.
 * \tparam CostType The type used to represent cost values.
 * \tparam Nat Template non-type parameter defining the kind of
 *             graph (directed / undirected), possible values are UNDIRECTED and
 *             DIRECTED.
 **/
template<
    typename NodeIdentifier,
    typename CostType,
    Nature Nat,
    typename GraphedType = int>
using graph_t = graph<
    /* key_type */ NodeIdentifier,
    /* graphed_type (no idea what this is, doesn't seem like it's used anywhere)
     */
    GraphedType,
    /* cost_type */ CostType,
    /* Nature */ Nat>;
