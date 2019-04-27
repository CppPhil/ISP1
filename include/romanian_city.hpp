/*!
 * \file romanian_city.hpp
 * \brief Exports the romanian_city enum and its associated functions.
 **/
#pragma once
#include <ostream> // std::ostream
#include <string>  // std::string

namespace isp1 {
/*!
 * \def ROMANIAN_CITY_X_MACRO
 * \brief X-Macro for the romanian cities.
 * \note See https://en.wikipedia.org/wiki/X_Macro
 **/
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

/*!
 * \brief Enum for the romanian cities.
 **/
enum class romanian_city {
#define X(CityName) CityName,
    ROMANIAN_CITY_X_MACRO
#undef X
};

/*!
 * \brief Converts a romanian_city into a string.
 * \param city The romanian_city to turn into a string.
 * \return The resulting string representation.
 **/
std::string to_string(romanian_city city);

/*!
 * \brief Converts a string to a romanian_city.
 * \param string The string to convert.
 * \return The resulting enumerator.
 * \throws logic_error If the string given is not valid.
 **/
romanian_city from_string(const std::string& string);

/*!
 * \brief Prints a romanian_city to an ostream.
 * \param os The ostream to print to.
 * \param city The romanian_city to print.
 * \return A reference to os.
 **/
std::ostream& operator<<(std::ostream& os, romanian_city city);
} // namespace isp1