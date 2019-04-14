#include <astar.hpp>
#include <iomanip>
#include <iostream>
#include <iterator>
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
    using Map = UndirectedGraph<RomanianCity>;
    Map romaniaMap;
    romaniaMap(RomanianCity::Oradea, RomanianCity::Zerind)         = 71;
    romaniaMap(RomanianCity::Zerind, RomanianCity::Arad)           = 75;
    romaniaMap(RomanianCity::Oradea, RomanianCity::Sibiu)          = 151;
    romaniaMap(RomanianCity::Arad, RomanianCity::Sibiu)            = 140;
    romaniaMap(RomanianCity::Arad, RomanianCity::Timisoara)        = 118;
    romaniaMap(RomanianCity::Timisoara, RomanianCity::Lugoj)       = 111;
    romaniaMap(RomanianCity::Lugoj, RomanianCity::Mehadia)         = 70;
    romaniaMap(RomanianCity::Mehadia, RomanianCity::Dobreta)       = 75;
    romaniaMap(RomanianCity::Dobreta, RomanianCity::Craiova)       = 120;
    romaniaMap(RomanianCity::RimnicuVilcea, RomanianCity::Craiova) = 146;
    romaniaMap(RomanianCity::Craiova, RomanianCity::Pitesti)       = 138;
    romaniaMap(RomanianCity::RimnicuVilcea, RomanianCity::Sibiu)   = 80;
    romaniaMap(RomanianCity::Sibiu, RomanianCity::Fagaras)         = 99;
    romaniaMap(RomanianCity::RimnicuVilcea, RomanianCity::Pitesti) = 97;
    romaniaMap(RomanianCity::Pitesti, RomanianCity::Bucharest)     = 101;
    romaniaMap(RomanianCity::Fagaras, RomanianCity::Bucharest)     = 211;
    romaniaMap(RomanianCity::Bucharest, RomanianCity::Giurgiu)     = 90;
    romaniaMap(RomanianCity::Bucharest, RomanianCity::Urziceni)    = 85;
    romaniaMap(RomanianCity::Urziceni, RomanianCity::Hirsova)      = 98;
    romaniaMap(RomanianCity::Hirsova, RomanianCity::Eforie)        = 86;
    romaniaMap(RomanianCity::Urziceni, RomanianCity::Vaslui)       = 142;
    romaniaMap(RomanianCity::Vaslui, RomanianCity::Iasi)           = 92;
    romaniaMap(RomanianCity::Iasi, RomanianCity::Neamt)            = 87;

    const unordered_map<RomanianCity, int> straightLineToBucharestMap(
        {{RomanianCity::Arad, 366},          {RomanianCity::Bucharest, 0},
         {RomanianCity::Craiova, 160},       {RomanianCity::Dobreta, 242},
         {RomanianCity::Eforie, 161},        {RomanianCity::Fagaras, 176},
         {RomanianCity::Giurgiu, 77},        {RomanianCity::Hirsova, 151},
         {RomanianCity::Iasi, 226},          {RomanianCity::Lugoj, 244},
         {RomanianCity::Mehadia, 241},       {RomanianCity::Neamt, 234},
         {RomanianCity::Oradea, 380},        {RomanianCity::Pitesti, 100},
         {RomanianCity::RimnicuVilcea, 193}, {RomanianCity::Sibiu, 253},
         {RomanianCity::Timisoara, 329},     {RomanianCity::Urziceni, 80},
         {RomanianCity::Vaslui, 199},        {RomanianCity::Zerind, 374}});

    cout
        << "\nSee "
           "https://csunplugged.files.wordpress.com/2012/09/romania-graph1.png "
           "for a visual representation of the Romania Graph.\n";

    const RomanianCity startCity{RomanianCity::Arad};
    const RomanianCity goalCity{RomanianCity::Bucharest};

    const auto heuristic
        = [&straightLineToBucharestMap, goalCity](RomanianCity city) {
              const auto iter = straightLineToBucharestMap.find(city);

              if (iter == end(straightLineToBucharestMap)) {
                  return numeric_limits<uint64_t>::max();
              }

              const uint64_t heuristicCost = iter->second;
              return heuristicCost;
          };

    Path<RomanianCity> aStarPath{aStar(
        romaniaMap,
        startCity,
        [&goalCity](RomanianCity city) { return city == goalCity; },
        heuristic)};

    cout << "\nCalculation of the shortest path from '" << startCity << "' to '"
         << goalCity << "':\n"
         << "A* total cost: " << aStarPath.g() << "\n\n";

    int step{1};
    int curAStarCumulativeGCost{0};
    for (const IdentifierWithCost<RomanianCity>& e : aStarPath) {
        cout << "Step " << step << " | ";

        const RomanianCity& cityNameKey{e.nodeIdentifier()};
        const auto          gCost = e.g();

        curAStarCumulativeGCost += gCost;

        cout << cityNameKey << " (" << curAStarCumulativeGCost << ")\n";

        ++step;
    }
}
