#include <ciso646> // not
#include <column.hpp>

column::column(value_type value) : m_value(value) {}

column::value_type column::value() const { return m_value; }

bool operator==(column lhs, column rhs) { return lhs.value() == rhs.value(); }

bool operator!=(column lhs, column rhs) { return not(lhs == rhs); }
