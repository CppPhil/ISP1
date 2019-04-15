#include <romanian_city.hpp>

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

ostream& operator<<(ostream& os, romanian_city city)
{
    os << to_string(city);
    return os;
}
