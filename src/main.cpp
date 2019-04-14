#include <astar.hpp>
#include <graph.hpp>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <unordered_map>

/**
 * @brief Romania Route Finding Problem using different search algorithms
 * @see https://csunplugged.files.wordpress.com/2012/09/romania-graph1.png
 */

int main()
{
    using Map = graph_undirected<std::string, int, std::uint64_t>;
    Map romaniaMap;
    romaniaMap("Oradea", "Zerind")          = 71;
    romaniaMap("Zerind", "Arad")            = 75;
    romaniaMap("Oradea", "Sibiu")           = 151;
    romaniaMap("Arad", "Sibiu")             = 140;
    romaniaMap("Arad", "Timisoara")         = 118;
    romaniaMap("Timisoara", "Lugoj")        = 111;
    romaniaMap("Lugoj", "Mehadia")          = 70;
    romaniaMap("Mehadia", "Drobeta")        = 75;
    romaniaMap("Drobeta", "Craiova")        = 120;
    romaniaMap("Rimnicu Vilcea", "Craiova") = 146;
    romaniaMap("Craiova", "Pitesti")        = 138;
    romaniaMap("Rimnicu Vilcea", "Sibiu")   = 80;
    romaniaMap("Sibiu", "Fagaras")          = 99;
    romaniaMap("Rimnicu Vilcea", "Pitesti") = 97;
    romaniaMap("Pitesti", "Bucharest")      = 101;
    romaniaMap("Fagaras", "Bucharest")      = 211;
    romaniaMap("Bucharest", "Giurgiu")      = 90;
    romaniaMap("Bucharest", "Urziceni")     = 85;
    romaniaMap("Urziceni", "Hirsova")       = 98;
    romaniaMap("Hirsova", "Eforie")         = 86;
    romaniaMap("Urziceni", "Vaslui")        = 142;
    romaniaMap("Vaslui", "Iasi")            = 92;
    romaniaMap("Iasi", "Neamt")             = 87;

    const std::unordered_map<std::string, int> straightLineToBucharestMap(
        {{"Arad", 366},    {"Bucharest", 0},   {"Craiova", 160},
         {"Drobeta", 242}, {"Eforie", 161},    {"Fagaras", 176},
         {"Giurgiu", 77},  {"Hirsova", 151},   {"Iasi", 226},
         {"Lugoj", 244},   {"Mehadia", 241},   {"Neamt", 234},
         {"Oradea", 380},  {"Pitesti", 100},   {"Rimnicu Vilcea", 193},
         {"Sibiu", 253},   {"Timisoara", 329}, {"Urziceni", 80},
         {"Vaslui", 199},  {"Zerind", 374}});

    std::cout
        << "\nSee "
           "https://csunplugged.files.wordpress.com/2012/09/romania-graph1.png "
           "for a visual representation of the Romania Graph.\n";

    const std::string startCity{"Arad"};
    const std::string goalCity{"Bucharest"};

    const auto heuristic = [&straightLineToBucharestMap, goalCity](const std::string& nodeIdentifier) {
        const auto iter = straightLineToBucharestMap.find(nodeIdentifier);

        if (iter == std::end(straightLineToBucharestMap)) {
            return std::numeric_limits<std::uint64_t>::max();
        }

        const std::uint64_t heuristicCost = iter->second;
        return heuristicCost;
    };

    isp1::Path<std::string> aStarPath = isp1::aStar(romaniaMap, startCity, [&goalCity](const std::string& nodeIdentifier) {
        return nodeIdentifier == goalCity;
    },
        heuristic    
    );

    std::cout << "\nCalculation of the shortest path from '" << startCity
              << "' to '" << goalCity << "':\n"
              << "A* total cost: " << aStarPath.g() << "\n\n";

    int step{1};
    int curAStarCumulativeGCost{0};
    for (const isp1::IdentifierWithCost<std::string>& e : aStarPath) 
    {
        std::cout << std::left << std::setw(13)
                  << ("Step " + std::to_string(step)) << " |" << std::right;

        const std::string& cityNameKey{e.nodeIdentifier};
        const auto         gCost = e.g;

        curAStarCumulativeGCost += gCost;

        std::cout << std::setw(21)
                  << (cityNameKey + " ("
                      + std::to_string(curAStarCumulativeGCost) + ")")
                  << '\n';
        ++step;
    }

#if 0
    const auto heuristicCallable
        = [&straightLineToBucharestMap, goalCity](
              const graph_undirected<std::string, int, int>::const_iterator& it)
        -> double {
        const std::string& cityName{it->first};
        const auto         iter = straightLineToBucharestMap.find(cityName);

        if (iter == std::end(straightLineToBucharestMap)) {
            return std::numeric_limits<double>::max();
        }

        const auto heuristicCost = iter->second;
        return heuristicCost;
    };

    Map::search_path aStarPath{isp1::aStar(
        romaniaMap,
        romaniaMap.find(startCity),
        [&goalCity](Map::const_iterator it) {
            const std::string& cityNameKey{it->first};
            return cityNameKey == goalCity;
        },
        heuristicCallable)};

    std::cout << "\nCalculation of the shortest path from '" << startCity
              << "' to '" << goalCity << "':\n"
              << "A* total cost: " << aStarPath.total_cost() << "\n\n";

    int step{1};
    int curAStarCumulativeGCost{0};
    for (; !aStarPath.empty(); ++step) {
        std::cout << std::left << std::setw(13)
                  << ("Step " + std::to_string(step)) << " |" << std::right;

        auto               pair          = aStarPath.front();
        auto               graphIterator = pair.first;
        const std::string& cityNameKey{graphIterator->first};
        const auto         gCost = pair.second;

        aStarPath.pop_front();

        curAStarCumulativeGCost += gCost;

        std::cout << std::setw(21)
                  << (cityNameKey + " ("
                      + std::to_string(curAStarCumulativeGCost) + ")")
                  << '\n';
    }
#endif
}
