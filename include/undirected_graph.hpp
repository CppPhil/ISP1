#pragma once
#include <cost.hpp>  // cost
#include <graph.hpp> // graph_undirected

template<typename NodeIdentifier, typename CostType = cost>
using undirected_graph = graph_undirected<
    /* key_type */ NodeIdentifier,
    /* graphed_type (no idea what this is, doesn't seem like it's used anywhere)
     */
    int,
    /* cost_type */ CostType>;
