#include <ciso646> // not
#include <column.hpp>

namespace isp1 {
column::column(value_type value) : m_value(value) {}

column::value_type column::value() const { return m_value; }

std::ostream& operator<<(std::ostream& os, column col)
{
    os << "{\"value\": " << col.value() << '}';
    return os;
}

bool operator<(column lhs, column rhs) { return lhs.value() < rhs.value(); }
} // namespace isp1