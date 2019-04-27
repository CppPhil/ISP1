#include <ciso646> // not
#include <row.hpp>

namespace isp1{
row::row(value_type value) : m_value(value) {}

row::value_type row::value() const { return m_value; }

bool operator==(row lhs, row rhs) { return lhs.value() == rhs.value(); }

bool operator!=(row lhs, row rhs) { return not(lhs == rhs); }
} // namespace isp1