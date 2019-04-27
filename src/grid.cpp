#include <algorithm> // std::remove_if
#include <ciso646>   // not, and
#include <cstddef>   // std::size_t
#include <grid.hpp>
#include <iterator>                      // std::distance
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find, pl::algo::transform
#include <sstream>                       // std::ostringstream
#include <stdexcept>                     // std::out_of_range

namespace isp1 {
grid::grid(column column_count, row row_count) : m_data()
{
    if (column_count.value() == 0) {
        throw std::out_of_range("column_count was 0 in grid constructor!");
    }

    if (row_count.value() == 0) {
        throw std::out_of_range("row_count was 0 in grid constructor!");
    }

    m_data = std::vector<std::vector<position_kind>>(
        column_count.value(),
        std::vector<position_kind>(row_count.value(), position_kind::empty));
}

column grid::column_count() const { return column(m_data.size()); }

row grid::row_count() const { return row(m_data.at(0).size()); }

position_kind& grid::at(position position)
{
    return m_data.at(position.column().value()).at(position.row().value());
}

const position_kind& grid::at(position position) const
{
    return const_cast<this_type*>(this)->at(position);
}

graph_t<position, cost, UNDIRECTED> grid::as_graph() const
{
    graph_t<position, cost, UNDIRECTED> result_graph;

    const cost cost_value = 1; // Cost is always 1 in a grid from one position
                               // to a neighboring one

    // Run over the entire grid
    for (std::size_t current_column_idx = 0;
         current_column_idx < column_count().value();
         ++current_column_idx) {
        for (std::size_t current_row_idx = 0;
             current_row_idx < row_count().value();
             ++current_row_idx) {
            const position current_position = position(
                column((current_column_idx)), row((current_row_idx)));

            // Get the neighbors of the current position
            std::vector<position> current_neighbors
                = neighbors(current_position);

            // Run over all the neighbors of the current position
            for (position current_neighbor : current_neighbors) {
                // Put the current position connected to the current neighbor
                // into the graph, if it isn't a wall
                if ((at(current_position) != position_kind::wall)
                    and (at(current_neighbor) != position_kind::wall)) {
                    result_graph(current_position, current_neighbor)
                        = cost_value;
                }
            }
        }
    }

    return result_graph;
}

void grid::insert_path(const path<position>& result_path)
{
    for (identifier_with_cost<position> id_w_c : result_path) {
        position_kind& cur_position_kind = at(id_w_c.node_identifier());

        if (cur_position_kind == position_kind::empty) {
            at(id_w_c.node_identifier()) = position_kind::on_path;
        }
    }
}

bool grid::has_goal() const { return goal().has_value(); }

tl::optional<position> grid::goal() const { return find(position_kind::goal); }

bool grid::has_start() const { return start().has_value(); }

tl::optional<position> grid::start() const
{
    return find(position_kind::start);
}

std::string grid::to_string() const
{
    const std::size_t columns = column_count().value();
    const std::size_t rows    = row_count().value();

    std::vector<std::string> column_wise_strings;

    std::ostringstream oss;

    for (std::size_t cur_col_idx = 0; cur_col_idx < columns; ++cur_col_idx) {
        for (std::size_t cur_row_idx = 0; cur_row_idx < rows; ++cur_row_idx) {
            const column cur_column(cur_col_idx);
            const row    cur_row(cur_row_idx);

            oss << at(position(cur_column, cur_row));
        }

        column_wise_strings.push_back(oss.str());
        oss.str("");
    }

    std::string buf;

    for (std::size_t cur_row_idx = 0; cur_row_idx < rows; ++cur_row_idx) {
        for (std::size_t cur_col_idx = 0; cur_col_idx < columns;
             ++cur_col_idx) {
            const std::string& cur_string = column_wise_strings.at(cur_col_idx);

            buf += cur_string.at(cur_row_idx);
        }

        buf += '\n';
    }

    oss << position_kind::start << ": start\n"
        << position_kind::goal << ": goal\n"
        << position_kind::empty << ": empty\n"
        << position_kind::wall << ": wall\n"
        << position_kind::on_path << ": on path";

    buf += oss.str();

    return buf;
}

std::ostream& operator<<(std::ostream& os, const grid& grid)
{
    grid.visualize(os);
    return os;
}

void grid::visualize(std::ostream& os) const { os << to_string(); }

std::vector<position_kind>& grid::get_column(column value)
{
    return m_data.at(value.value());
}

const std::vector<position_kind>& grid::get_column(column value) const
{
    return const_cast<this_type*>(this)->get_column(value);
}

tl::optional<position> grid::find(position_kind kind) const
{
    for (std::size_t current_column_idx = 0;
         current_column_idx < column_count().value();
         ++current_column_idx) {
        const std::vector<position_kind>& current_column
            = get_column(column(current_column_idx));

        const std::vector<position_kind>::const_iterator it
            = pl::algo::find(current_column, kind);

        if (it != current_column.end()) {
            return position(
                column(current_column_idx),
                row(std::distance(current_column.begin(), it)));
        }
    }

    return tl::nullopt;
}

const std::size_t neighbor_offset = 1;

tl::optional<position> grid::top_neighbor(position pos) const
{
    if (pos.row().value() == 0) { return tl::nullopt; }

    return tl::make_optional(
        position(pos.column(), row(pos.row().value() - neighbor_offset)));
}

tl::optional<position> grid::bottom_neighbor(position pos) const
{
    const std::size_t max_row = row_count().value() - 1;

    if (pos.row().value() >= max_row) { return tl::nullopt; }

    return tl::make_optional(
        position(pos.column(), row(pos.row().value() + neighbor_offset)));
}

tl::optional<position> grid::left_neighbor(position pos) const
{
    if (pos.column().value() == 0) { return tl::nullopt; }

    return tl::make_optional(
        position(column(pos.column().value() - neighbor_offset), pos.row()));
}

tl::optional<position> grid::right_neighbor(position pos) const
{
    const std::size_t max_column = column_count().value() - 1;

    if (pos.column().value() >= max_column) { return tl::nullopt; }

    return tl::make_optional(
        position(column(pos.column().value() + neighbor_offset), pos.row()));
}

std::vector<position> grid::neighbors(position pos) const
{
    // Get all the optionals
    std::vector<tl::optional<position>> optional_positions(
        {top_neighbor(pos),
         bottom_neighbor(pos),
         left_neighbor(pos),
         right_neighbor(pos)});

    // Remove all those that don't have a value.
    // See: https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
    optional_positions.erase(
        std::remove_if(
            optional_positions.begin(),
            optional_positions.end(),
            [](const tl::optional<position>& opt) {
                return not opt.has_value();
            }),
        optional_positions.end());

    // Unpack the optionals
    std::vector<position> result(
        optional_positions.size(), position(column(0), row(0)));
    pl::algo::transform(
        optional_positions,
        result.begin(),
        [](const tl::optional<position>& opt) { return *opt; });

    return result;
}
} // namespace isp1