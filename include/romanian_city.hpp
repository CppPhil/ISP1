#pragma once
#include <iosfwd>             // std::ostream
#include <pl/string_view.hpp> // pl::string_view

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

enum class RomanianCity {
#define X(CityName) CityName,
    ROMANIAN_CITY_X_MACRO
#undef X
};

constexpr pl::string_view toString(RomanianCity city)
{
    using namespace pl::literals::string_view_literals;

    pl::string_view result{};

    switch (city) {
#define X(CityName) \
    case RomanianCity::CityName: result = #CityName; break;
        ROMANIAN_CITY_X_MACRO
#undef X
    }

    if (result == "RimnicuVilcea"_sv) { return "Rimnicu Vilcea"; }

    return result;
}

std::ostream& operator<<(std::ostream& os, RomanianCity city);
