#include <a_star.hpp> // a_star
#include <non_monotonic.hpp> // make_non_monotonic_graph, non_monotonic_goal_node, non_monotonic_heuristic
#include <pl/except.hpp> // handle_exceptions
#include <pl/timer.hpp>  // timer
#include <romania.hpp>   // create_romania_map, romania_heuristic

int main()
{
    try {
        timer timer;

        const graph_t<romanian_city, cost, UNDIRECTED> romania_map
            = create_romania_map();

        const romanian_city start_city = romanian_city::Arad;

        const auto is_goal_city
            = [](romanian_city city) { return city == goal_city; };

        timer.reset();
        const path<romanian_city> a_star_path = a_star(
            romania_map,
            vector<romanian_city>({start_city}),
            is_goal_city,
            &romania_heuristic);
        const chrono::steady_clock::duration a_star_romania_time_taken
            = timer.elapsed_time();

        cout << "\nCalculation of the shortest path from '" << start_city
             << "' to '" << goal_city << "':\n"
             << "A* total cost: " << a_star_path.g() << "\n\n"
             << "path: " << a_star_path << '\n'
             << "time taken: "
             << chrono::duration_cast<chrono::nanoseconds>(
                    a_star_romania_time_taken)
                    .count()
             << "ns\n";

        timer.reset();
        a_star(
            romania_map,
            vector<romanian_city>({start_city}),
            is_goal_city,
            [](romanian_city) { return 0; });
        const chrono::steady_clock::duration a_star_romania_dijkstra_time_taken
            = timer.elapsed_time();
        cout << "dijkstra time taken: "
             << chrono::duration_cast<chrono::nanoseconds>(
                    a_star_romania_dijkstra_time_taken)
                    .count()
             << "ns\n";

        // non monotonic heuristic
        const graph_t<string, cost, DIRECTED> g = make_non_monotonic_graph();

        const string start_node = "START";

        const path<string> p = a_star(
            g,
            vector<string>({start_node}),
            [](string str) { return str == non_monotonic_goal_node; },
            &non_monotonic_heuristic);

        cout << "\ntotal cost: " << p.g();
        cout << "\np: " << p << '\n';
    }
    catch (...) {
        handle_exceptions();
    }
}
