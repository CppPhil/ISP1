#include <grid_world.hpp>         // isp1::create_grid_world
#include <manhattan_distance.hpp> // isp1::manhattan_distance
#include <non_monotonic.hpp> // isp1::make_non_monotonic_graph, isp1::non_monotonic_goal_node, isp1::non_monotonic_heuristic
#include <pl/except.hpp>     // pl::handle_exceptions
#include <romania.hpp> // isp1::create_romania_map, isp1::romania_heuristic
#include <run_graph_example.hpp> // isp1::run_graph_example

int main()
{
    try {
        std::cout << "\nAPPLICATION START\n\n";

        // Romania
        const isp1::graph_t<isp1::romanian_city, isp1::cost, UNDIRECTED>
            romania_map = isp1::create_romania_map();

        const isp1::romanian_city start_city = isp1::romanian_city::Arad;

        const auto is_goal_city
            = [](isp1::romanian_city city) { return city == isp1::goal_city; };

        std::cout << "Calculation of the shortest path from '" << start_city
                  << "' to '" << isp1::goal_city << "':\n";

        isp1::run_graph_example(
            romania_map,
            std::vector<isp1::romanian_city>({start_city}),
            is_goal_city,
            &isp1::romania_heuristic);

        std::cout << "Dijkstra:\n";
        isp1::run_graph_example(
            romania_map,
            std::vector<isp1::romanian_city>({start_city}),
            is_goal_city,
            [](isp1::romanian_city) { return 0; });

        // non monotonic heuristic
        const isp1::graph_t<std::string, isp1::cost, DIRECTED> g
            = isp1::make_non_monotonic_graph();

        const std::string start_node = "START";

        std::cout << "Non monotonic example:\n";
        isp1::run_graph_example(
            g,
            std::vector<std::string>({start_node}),
            [](std::string str) {
                return str == isp1::non_monotonic_goal_node;
            },
            &isp1::non_monotonic_heuristic,
            false);

        // Grid world
        std::cout << "Grid world example:\n";
        isp1::grid grid_world = isp1::create_grid_world();

        const isp1::graph_t<isp1::position, isp1::cost, UNDIRECTED>
                             grid_world_graph = grid_world.graph();
        const isp1::position grid_start       = grid_world.start().value();
        const isp1::position grid_goal        = grid_world.goal().value();
        const auto           grid_heuristic = [grid_goal](isp1::position pos) {
            return isp1::manhattan_distance(pos, grid_goal);
        };
        const isp1::path<isp1::position> grid_path = isp1::run_graph_example(
            grid_world_graph,
            std::vector<isp1::position>({grid_start}),
            [grid_goal](isp1::position pos) { return pos == grid_goal; },
            grid_heuristic);

        std::cout << "grid without path:\n" << grid_world << "\n\n";

        grid_world.insert_path(grid_path);

        std::cout << "grid with path:\n" << grid_world << '\n';
    }
    catch (...) {
        pl::handle_exceptions();
    }
}
