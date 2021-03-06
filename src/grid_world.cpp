#include <grid_world.hpp>

namespace isp1 {
grid create_grid_world()
{
    grid g(column(15), row(15));

    const auto w = [&g](std::size_t x, std::size_t y) {
        g.at(position(column(x), row(y))) = position_kind::wall;
    };

    g.at(position(column(0), row(12))) = position_kind::start;
    g.at(position(column(13), row(2))) = position_kind::goal;

    // line from [5, 2] to [12, 2]
    for (std::size_t x = 5; x <= 12; ++x) { w(x, 2); }

    // line from [12, 3] to [12, 12]
    for (std::size_t y = 3; y <= 12; ++y) { w(12, y); }

    // line from [2, 12] to [11, 12]
    for (std::size_t x = 2; x <= 11; ++x) { w(x, 12); }

    return g;
}
} // namespace isp1