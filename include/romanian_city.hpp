#pragma once
#include <namespaces.hpp>
#include <ostream> // ostream
#include <string>  // string

#define ROMANIAN_CITY_X_MACRO \
    X(Arad)                   \
    X(Bucharest)              \
    X(Craiova)                \
    X(Dobreta)                \
    X(Eforie)                 \
    X(Fagaras)                \
    X(Giurgiu)                \
    X(Hirsova)                \
    X(Iasi)                   \
    X(Lugoj)                  \
    X(Mehadia)                \
    X(Neamt)                  \
    X(Oradea)                 \
    X(Pitesti)                \
    X(RimnicuVilcea)          \
    X(Sibiu)                  \
    X(Timisoara)              \
    X(Urziceni)               \
    X(Vaslui)                 \
    X(Zerind)

enum class romanian_city {
#define X(CityName) CityName,
    ROMANIAN_CITY_X_MACRO
#undef X
};

string toString(romanian_city city);

ostream& operator<<(ostream& os, romanian_city city);
