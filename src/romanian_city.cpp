#include <ostream> // std::ostream
#include <romanian_city.hpp>

namespace isp1 {
std::ostream& operator<<(std::ostream& os, RomanianCity city)
{
    return os << toString(city);
}
} // namespace isp1
