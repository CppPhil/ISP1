#include <ciso646> // and, not
#include <position.hpp>

namespace isp1 {
position::position(class column column, class row row)
    : m_column(column), m_row(row)
{
}

column position::column() const { return m_column; }

row position::row() const { return m_row; }

bool operator==(position lhs, position rhs)
{
    return (lhs.column() == rhs.column()) and (lhs.row() == rhs.row());
}

bool operator!=(position lhs, position rhs) { return not(lhs == rhs); }
} // namespace isp1