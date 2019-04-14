#include <astar.hpp>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <romanian_city.hpp>
#include <undirected_graph.hpp>
#include <unordered_map>

/**
 * @brief Romania Route Finding Problem using different search algorithms
 * @see https://csunplugged.files.wordpress.com/2012/09/romania-graph1.png
 */

int main()
{
    using Map = isp1::UndirectedGraph<isp1::RomanianCity>;
    Map romaniaMap;
    romaniaMap(isp1::RomanianCity::Oradea, isp1::RomanianCity::Zerind)   = 71;
    romaniaMap(isp1::RomanianCity::Zerind, isp1::RomanianCity::Arad)     = 75;
    romaniaMap(isp1::RomanianCity::Oradea, isp1::RomanianCity::Sibiu)    = 151;
    romaniaMap(isp1::RomanianCity::Arad, isp1::RomanianCity::Sibiu)      = 140;
    romaniaMap(isp1::RomanianCity::Arad, isp1::RomanianCity::Timisoara)  = 118;
    romaniaMap(isp1::RomanianCity::Timisoara, isp1::RomanianCity::Lugoj) = 111;
    romaniaMap(isp1::RomanianCity::Lugoj, isp1::RomanianCity::Mehadia)   = 70;
    romaniaMap(isp1::RomanianCity::Mehadia, isp1::RomanianCity::Dobreta) = 75;
    romaniaMap(isp1::RomanianCity::Dobreta, isp1::RomanianCity::Craiova) = 120;
    romaniaMap(isp1::RomanianCity::RimnicuVilcea, isp1::RomanianCity::Craiova)
        = 146;
    romaniaMap(isp1::RomanianCity::Craiova, isp1::RomanianCity::Pitesti) = 138;
    romaniaMap(isp1::RomanianCity::RimnicuVilcea, isp1::RomanianCity::Sibiu)
        = 80;
    romaniaMap(isp1::RomanianCity::Sibiu, isp1::RomanianCity::Fagaras) = 99;
    romaniaMap(isp1::RomanianCity::RimnicuVilcea, isp1::RomanianCity::Pitesti)
        = 97;
    romaniaMap(isp1::RomanianCity::Pitesti, isp1::RomanianCity::Bucharest)
        = 101;
    romaniaMap(isp1::RomanianCity::Fagaras, isp1::RomanianCity::Bucharest)
        = 211;
    romaniaMap(isp1::RomanianCity::Bucharest, isp1::RomanianCity::Giurgiu) = 90;
    romaniaMap(isp1::RomanianCity::Bucharest, isp1::RomanianCity::Urziceni)
        = 85;
    romaniaMap(isp1::RomanianCity::Urziceni, isp1::RomanianCity::Hirsova) = 98;
    romaniaMap(isp1::RomanianCity::Hirsova, isp1::RomanianCity::Eforie)   = 86;
    romaniaMap(isp1::RomanianCity::Urziceni, isp1::RomanianCity::Vaslui)  = 142;
    romaniaMap(isp1::RomanianCity::Vaslui, isp1::RomanianCity::Iasi)      = 92;
    romaniaMap(isp1::RomanianCity::Iasi, isp1::RomanianCity::Neamt)       = 87;

    const std::unordered_map<isp1::RomanianCity, int>
        straightLineToBucharestMap({{isp1::RomanianCity::Arad, 366},
                                    {isp1::RomanianCity::Bucharest, 0},
                                    {isp1::RomanianCity::Craiova, 160},
                                    {isp1::RomanianCity::Dobreta, 242},
                                    {isp1::RomanianCity::Eforie, 161},
                                    {isp1::RomanianCity::Fagaras, 176},
                                    {isp1::RomanianCity::Giurgiu, 77},
                                    {isp1::RomanianCity::Hirsova, 151},
                                    {isp1::RomanianCity::Iasi, 226},
                                    {isp1::RomanianCity::Lugoj, 244},
                                    {isp1::RomanianCity::Mehadia, 241},
                                    {isp1::RomanianCity::Neamt, 234},
                                    {isp1::RomanianCity::Oradea, 380},
                                    {isp1::RomanianCity::Pitesti, 100},
                                    {isp1::RomanianCity::RimnicuVilcea, 193},
                                    {isp1::RomanianCity::Sibiu, 253},
                                    {isp1::RomanianCity::Timisoara, 329},
                                    {isp1::RomanianCity::Urziceni, 80},
                                    {isp1::RomanianCity::Vaslui, 199},
                                    {isp1::RomanianCity::Zerind, 374}});

    std::cout
        << "\nSee "
           "https://csunplugged.files.wordpress.com/2012/09/romania-graph1.png "
           "for a visual representation of the Romania Graph.\n";

    const isp1::RomanianCity startCity{isp1::RomanianCity::Arad};
    const isp1::RomanianCity goalCity{isp1::RomanianCity::Bucharest};

    const auto heuristic
        = [&straightLineToBucharestMap, goalCity](isp1::RomanianCity city) {
              const auto iter = straightLineToBucharestMap.find(city);

              if (iter == std::end(straightLineToBucharestMap)) {
                  return std::numeric_limits<std::uint64_t>::max();
              }

              const std::uint64_t heuristicCost = iter->second;
              return heuristicCost;
          };

    isp1::Path<isp1::RomanianCity> aStarPath{isp1::aStar(
        romaniaMap,
        startCity,
        [&goalCity](isp1::RomanianCity city) { return city == goalCity; },
        heuristic)};

    std::cout << "\nCalculation of the shortest path from '" << startCity
              << "' to '" << goalCity << "':\n"
              << "A* total cost: " << aStarPath.g() << "\n\n";

    int step{1};
    int curAStarCumulativeGCost{0};
    for (const isp1::IdentifierWithCost<isp1::RomanianCity>& e : aStarPath) {
        std::cout << "Step " << step << " | ";

        const isp1::RomanianCity& cityNameKey{e.nodeIdentifier()};
        const auto                gCost = e.g();

        curAStarCumulativeGCost += gCost;

        std::cout << cityNameKey << " (" << curAStarCumulativeGCost << ")\n";

        ++step;
    }
}
