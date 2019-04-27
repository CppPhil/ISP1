#include <ciso646> // not
#include <row.hpp>

namespace isp1 {
row::row(value_type value) : m_value(value) {}

row::value_type row::value() const { return m_value; }

std::ostream& operator<<(std::ostream& os, row row)
{
    os << "{\"value\": " << row.value() << '}';
    return os;
}

bool operator<(row lhs, row rhs) { return lhs.value() < rhs.value(); }
} // namespace isp1