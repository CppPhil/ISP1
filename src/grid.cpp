#include <grid.hpp>

#include <iostream>

namespace isp1{
grid::grid(column column_count, row row_count)
    : m_data(
        column_count.value(),
        std::vector<position_kind>(row_count.value(), position_kind::empty))
{

    std::cerr << "m_data.size(): " << m_data.size() << '\n';
    
    std::cerr << "subarrays:\n";

    for (const auto & r : m_data) {
        std::cerr << r.size() << '\n';
    }
}
} // namespace isp1