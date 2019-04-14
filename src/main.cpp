#include <a_star.hpp>
#include <iomanip>
#include <iostream>
#include <limits>
#include <namespaces.hpp>
#include <romanian_city.hpp>
#include <undirected_graph.hpp>
#include <unordered_map>

/**
 * @brief Romania Route Finding Problem using different search algorithms
 * @see https://csunplugged.files.wordpress.com/2012/09/romania-graph1.png
 */

int main()
{
    undirected_graph<romanian_city> romania_map;
    romania_map(romanian_city::Oradea, romanian_city::Zerind)         = 71;
    romania_map(romanian_city::Zerind, romanian_city::Arad)           = 75;
    romania_map(romanian_city::Oradea, romanian_city::Sibiu)          = 151;
    romania_map(romanian_city::Arad, romanian_city::Sibiu)            = 140;
    romania_map(romanian_city::Arad, romanian_city::Timisoara)        = 118;
    romania_map(romanian_city::Timisoara, romanian_city::Lugoj)       = 111;
    romania_map(romanian_city::Lugoj, romanian_city::Mehadia)         = 70;
    romania_map(romanian_city::Mehadia, romanian_city::Dobreta)       = 75;
    romania_map(romanian_city::Dobreta, romanian_city::Craiova)       = 120;
    romania_map(romanian_city::RimnicuVilcea, romanian_city::Craiova) = 146;
    romania_map(romanian_city::Craiova, romanian_city::Pitesti)       = 138;
    romania_map(romanian_city::RimnicuVilcea, romanian_city::Sibiu)   = 80;
    romania_map(romanian_city::Sibiu, romanian_city::Fagaras)         = 99;
    romania_map(romanian_city::RimnicuVilcea, romanian_city::Pitesti) = 97;
    romania_map(romanian_city::Pitesti, romanian_city::Bucharest)     = 101;
    romania_map(romanian_city::Fagaras, romanian_city::Bucharest)     = 211;
    romania_map(romanian_city::Bucharest, romanian_city::Giurgiu)     = 90;
    romania_map(romanian_city::Bucharest, romanian_city::Urziceni)    = 85;
    romania_map(romanian_city::Urziceni, romanian_city::Hirsova)      = 98;
    romania_map(romanian_city::Hirsova, romanian_city::Eforie)        = 86;
    romania_map(romanian_city::Urziceni, romanian_city::Vaslui)       = 142;
    romania_map(romanian_city::Vaslui, romanian_city::Iasi)           = 92;
    romania_map(romanian_city::Iasi, romanian_city::Neamt)            = 87;

    const unordered_map<romanian_city, int> straight_line_to_bucharest_map(
        {{romanian_city::Arad, 366},          {romanian_city::Bucharest, 0},
         {romanian_city::Craiova, 160},       {romanian_city::Dobreta, 242},
         {romanian_city::Eforie, 161},        {romanian_city::Fagaras, 176},
         {romanian_city::Giurgiu, 77},        {romanian_city::Hirsova, 151},
         {romanian_city::Iasi, 226},          {romanian_city::Lugoj, 244},
         {romanian_city::Mehadia, 241},       {romanian_city::Neamt, 234},
         {romanian_city::Oradea, 380},        {romanian_city::Pitesti, 100},
         {romanian_city::RimnicuVilcea, 193}, {romanian_city::Sibiu, 253},
         {romanian_city::Timisoara, 329},     {romanian_city::Urziceni, 80},
         {romanian_city::Vaslui, 199},        {romanian_city::Zerind, 374}});

    cout
        << "\nSee "
           "https://csunplugged.files.wordpress.com/2012/09/romania-graph1.png "
           "for a visual representation of the Romania Graph.\n";

    const romanian_city start_city{romanian_city::Arad};
    const romanian_city goal_city{romanian_city::Bucharest};

    const auto heuristic
        = [&straight_line_to_bucharest_map, goal_city](romanian_city city) {
              const auto iter = straight_line_to_bucharest_map.find(city);

              if (iter == straight_line_to_bucharest_map.end()) {
                  return numeric_limits<uint64_t>::max();
              }

              const uint64_t heuristic_cost = iter->second;
              return heuristic_cost;
          };

    path<romanian_city> a_star_path{a_star(
        romania_map,
        start_city,
        [&goal_city](romanian_city city) { return city == goal_city; },
        heuristic)};

    cout << "\nCalculation of the shortest path from '" << start_city
         << "' to '" << goal_city << "':\n"
         << "A* total cost: " << a_star_path.g() << "\n\n";

    int step{1};
    int current_a_star_cumulative_g_cost{0};
    for (const identifier_with_cost<romanian_city>& e : a_star_path) {
        cout << "Step " << step << " | ";

        const romanian_city& city_name{e.node_identifier()};
        const auto           g_cost = e.g();

        current_a_star_cumulative_g_cost += g_cost;

        cout << city_name << " (" << current_a_star_cumulative_g_cost << ")\n";

        ++step;
    }
}
