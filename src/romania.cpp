#include <limits> // std::numeric_limits
#include <romania.hpp>
#include <unordered_map> // std::unordered_map

namespace isp1 {
/*!
 * \brief Map that maps the cities of Romania to their heuristic (h) values,
 *        which represent the straight line distance to the goal city
 *        (Bucharest).
 **/
const std::unordered_map<romanian_city, int> straight_line_to_bucharest_map(
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

graph_t<romanian_city, cost, UNDIRECTED> create_romania_map()
{
    graph_t<romanian_city, cost, UNDIRECTED> romania_map;

    //          From                   To                               g
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

    return romania_map;
}

std::uint64_t romania_heuristic(romanian_city city)
{
    const auto iter = straight_line_to_bucharest_map.find(city);

    if (iter == straight_line_to_bucharest_map.end()) {
        return std::numeric_limits<std::uint64_t>::max();
    }

    const std::uint64_t heuristic_cost = iter->second;
    return heuristic_cost;
}
} // namespace isp1
