#include <grid.hpp>

namespace isp1 {
grid::grid(column column_count, row row_count)
    : m_data(
        column_count.value(),
        std::vector<position_kind>(row_count.value(), position_kind::empty))
{
}
} // namespace isp1