#include <cmath> // std::abs
#include <manhattan_distance.hpp>

namespace isp1 {
std::uint64_t manhattan_distance(position pos1, position pos2)
{
    const std::int64_t x1 = pos1.column().value();
    const std::int64_t x2 = pos2.column().value();

    const std::int64_t y1 = pos1.row().value();
    const std::int64_t y2 = pos2.row().value();

    return std::abs(x1 - x2) + std::abs(y1 - y2);
}
} // namespace isp1