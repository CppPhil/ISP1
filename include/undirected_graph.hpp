#pragma once
#include <cost.hpp>  // Cost
#include <graph.hpp> // graph_undirected

template<typename NodeIdentifier, typename CostType = Cost>
using UndirectedGraph = graph_undirected<
    /* key_type */ NodeIdentifier,
    /* graphed_type (no idea what this is, doesn't seem like it's used anywhere)
     */
    int,
    /* cost_type */ CostType>;
