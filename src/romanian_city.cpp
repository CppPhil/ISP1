#include <ostream> // std::ostream
#include <romanian_city.hpp>

std::ostream& operator<<(std::ostream& os, RomanianCity city)
{
    return os << toString(city);
}
