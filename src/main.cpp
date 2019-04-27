#include <non_monotonic.hpp> // isp1::make_non_monotonic_graph, isp1::non_monotonic_goal_node, isp1::non_monotonic_heuristic
#include <pl/except.hpp>     // pl::handle_exceptions
#include <romania.hpp> // isp1::create_romania_map, isp1::romania_heuristic
#include <run_graph_example.hpp> // isp1::run_graph_example

#include <grid.hpp>

inline void grid_test()
{
    using namespace isp1;
    using std::cout;

    cout << std::unitbuf << std::boolalpha;

    grid g(column(5), row(7));

    cout << "column_count: " << g.column_count().value() << '\n'
         << "row_count: " << g.row_count().value() << '\n';

    g.at(position(column(0), row(0))) = position_kind::start;
    g.at(position(column(4), row(6))) = position_kind::goal;
    g.at(position(column(0), row(5))) = position_kind::wall;
    g.at(position(column(1), row(5))) = position_kind::wall;
    g.at(position(column(3), row(5))) = position_kind::wall;
    g.at(position(column(4), row(5))) = position_kind::wall;

    cout << g << '\n';

    graph_t<position, cost, UNDIRECTED> graph = g.as_graph();

    const position       goal     = *g.goal();
    const path<position> path_res = isp1::a_star(
        graph,
        std::vector<position>{*g.start()},
        [&goal](const position& pos) { return pos == goal; },
        [&goal](const position& pos) {
            return std::abs(
                       static_cast<int>(goal.column().value())
                       - static_cast<int>(pos.column().value()))
                   + std::abs(
                       static_cast<int>(goal.row().value())
                       - static_cast<int>(pos.row().value()));
        });

    cout << "path:\n" << path_res << '\n';

    g.insert_path(path_res);

    cout << g << '\n';
}

int main()
{
    try {
        std::cout << "\nAPPLICATION START\n\n";

        grid_test();

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
            &isp1::non_monotonic_heuristic);
    }
    catch (...) {
        pl::handle_exceptions();
    }
}
