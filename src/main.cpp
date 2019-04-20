#include <non_monotonic.hpp> // make_non_monotonic_graph, non_monotonic_goal_node, non_monotonic_heuristic
#include <pl/except.hpp>         // handle_exceptions
#include <romania.hpp>           // create_romania_map, romania_heuristic
#include <run_graph_example.hpp> // run_graph_example

int main()
{
    try {
        cout << "\nAPPLICATION START\n\n";

        const graph_t<romanian_city, cost, UNDIRECTED> romania_map
            = create_romania_map();

        const romanian_city start_city = romanian_city::Arad;

        const auto is_goal_city
            = [](romanian_city city) { return city == goal_city; };

        cout << "Calculation of the shortest path from '" << start_city
             << "' to '" << goal_city << "':\n";

        run_graph_example(
            romania_map,
            vector<romanian_city>({start_city}),
            is_goal_city,
            &romania_heuristic);

        cout << "Dijkstra:\n";
        run_graph_example(
            romania_map,
            vector<romanian_city>({start_city}),
            is_goal_city,
            [](romanian_city) { return 0; });

        // non monotonic heuristic
        const graph_t<string, cost, DIRECTED> g = make_non_monotonic_graph();

        const string start_node = "START";

        cout << "Non monotonic example:\n";
        run_graph_example(
            g,
            vector<string>({start_node}),
            [](string str) { return str == non_monotonic_goal_node; },
            &non_monotonic_heuristic);
    }
    catch (...) {
        handle_exceptions();
    }
}
