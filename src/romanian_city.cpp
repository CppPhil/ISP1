#include <romanian_city.hpp>
#include <stdexcept> // logic_error

string to_string(romanian_city city)
{
    string result;

    // The # preprocessor operator 'stringifies' its input
    switch (city) {
#define X(city_name) \
    case romanian_city::city_name: result = #city_name; break;
        ROMANIAN_CITY_X_MACRO
#undef X
    }

    // Special casing for Rimnicu Vilcea ...
    if (result == "RimnicuVilcea") { return "Rimnicu Vilcea"; }

    return result;
}

romanian_city from_string(const string& string)
{
#define X(city_name)                                     \
    if (to_string(romanian_city::city_name) == string) { \
        return romanian_city::city_name;                 \
    }
    ROMANIAN_CITY_X_MACRO
#undef X

    throw logic_error(
        "Invalid string passed to from_string in romanian_city.cpp");
}

ostream& operator<<(ostream& os, romanian_city city)
{
    os << to_string(city);
    return os;
}
