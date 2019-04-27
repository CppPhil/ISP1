#include <ciso646> // and, not
#include <position.hpp>
#include <tuple> // std::tie

namespace isp1 {
position::position(class column column, class row row)
    : m_column(column), m_row(row)
{
}

column position::column() const { return m_column; }

row position::row() const { return m_row; }

bool operator<(position lhs, position rhs)
{
    // See: https://en.cppreference.com/w/cpp/utility/tuple/tie
    // These local variables need to be here so that we have lvalues of them.
    // std::tie does not accept rvalues.
    const column lhs_column = lhs.column();
    const row    lhs_row    = lhs.row();

    const column rhs_column = rhs.column();
    const row    rhs_row    = rhs.row();

    return std::tie(lhs_column, lhs_row) < std::tie(rhs_column, rhs_row);
}
} // namespace isp1