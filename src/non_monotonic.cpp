#include <limits> // numeric_limits
#include <non_monotonic.hpp>

graph_t<string, cost, DIRECTED> make_non_monotonic_graph()
{
    graph_t<string, cost, DIRECTED> g;

    // begin,  target, g
    g("START", "B") = 5;
    g("START", "C") = 5;
    g("B", "D")     = 6;
    g("C", "D")     = 5;
    g("D", "E")     = 5;
    g("E", "GOAL")  = 5;

    return g;
}

cost non_monotonic_heuristic(string node_identifier)
{
    // Map the node identifiers (strings) to their h values.
    if (node_identifier == "START") { return 9; }
    else if (node_identifier == "B") {
        return 7;
    }
    else if (node_identifier == "C") {
        return 8;
    }
    else if (node_identifier == "D") {
        return 1;
    }
    else if (node_identifier == "E") {
        return 1;
    }
    else if (node_identifier == "GOAL") {
        return 0;
    }

    return numeric_limits<cost>::max();
}
