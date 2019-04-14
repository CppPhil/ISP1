#include <romanian_city.hpp>

string toString(RomanianCity city)
{
    string result{};

    switch (city) {
#define X(CityName) \
    case RomanianCity::CityName: result = #CityName; break;
        ROMANIAN_CITY_X_MACRO
#undef X
    }

    if (result == "RimnicuVilcea") { return "Rimnicu Vilcea"; }

    return result;
}

ostream& operator<<(ostream& os, RomanianCity city)
{
    return os << toString(city);
}
