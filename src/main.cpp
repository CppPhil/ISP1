#include <a_star.hpp>    // a_star
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
        const path<romanian_city> a_star_path
            = a_star(romania_map, start_city, is_goal_city, &romania_heuristic);
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
        a_star(romania_map, start_city, is_goal_city, [](romanian_city) {
            return 0;
        });
        const chrono::steady_clock::duration a_star_romania_dijkstra_time_taken
            = timer.elapsed_time();
        cout << "dijkstra time taken: "
             << chrono::duration_cast<chrono::nanoseconds>(
                    a_star_romania_dijkstra_time_taken)
                    .count()
             << "ns\n";

        // non monotonic heuristic
        graph_t<string, cost, DIRECTED> g;
        g("START", "B") = 5;
        g("START", "C") = 5;
        g("B", "D")     = 6;
        g("C", "D")     = 5;
        g("D", "E")     = 5;
        g("E", "GOAL")  = 5;

        const auto heuristic = [](string node) -> cost {
            if (node == "START") { return 9; }
            else if (node == "B") {
                return 7;
            }
            else if (node == "C") {
                return 8;
            }
            else if (node == "D") {
                return 1;
            }
            else if (node == "E") {
                return 1;
            }
            else if (node == "GOAL") {
                return 0;
            }

            return numeric_limits<cost>::max();
        };

        const string start_node = "START";

        const path<string> p = a_star(
            g, start_node, [](string str) { return str == "GOAL"; }, heuristic);

        cout << "\ntotal cost: " << p.g();
        cout << "\np: " << p << '\n';
    }
    catch (...) {
        handle_exceptions();
    }
}
