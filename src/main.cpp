#include <a_star.hpp>  // a_star
#include <romania.hpp> // create_romania_map, romania_heuristic

int main()
{
    const graph_t<romanian_city, cost, UNDIRECTED> romania_map
        = create_romania_map();

    const romanian_city start_city = romanian_city::Arad;

    const path<romanian_city> a_star_path = a_star(
        romania_map,
        start_city,
        [](romanian_city city) { return city == goal_city; },
        &romania_heuristic);

    cout << "\nCalculation of the shortest path from '" << start_city
         << "' to '" << goal_city << "':\n"
         << "A* total cost: " << a_star_path.g() << "\n\n";

    int step                             = 1;
    int current_a_star_cumulative_g_cost = 0;
    for (const identifier_with_cost<romanian_city>& e : a_star_path) {
        cout << "Step " << step << " | ";

        const romanian_city& city_name = e.node_identifier();
        const auto           g_cost    = e.g();

        current_a_star_cumulative_g_cost += g_cost;

        cout << city_name << " (" << current_a_star_cumulative_g_cost << ")\n";

        ++step;
    }
}
