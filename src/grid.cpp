#include <cstddef> // std::size_t
#include <grid.hpp>
#include <iterator>                      // std::distance
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find

namespace isp1 {
grid::grid(column column_count, row row_count)
    : m_data(
        column_count.value(),
        std::vector<position_kind>(row_count.value(), position_kind::empty))
{
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
            const std::vector<position> current_neighbors
                = neighbors(current_position);

            // Run over all the neighbors of the current position
            for (position current_neighbor : current_neighbors) {
                // Put the current position connected to the current neighbor
                // into the graph
                result_graph(current_position, current_neighbor) = cost_value;
            }
        }
    }
}

void grid::insert_path(const path<position>& result_path)
{
    for (identifier_with_cost<position> id_w_c : result_path) {
        at(id_w_c.node_identifier()) = position_kind::on_path;
    }
}

bool grid::has_goal() const { return goal().has_value(); }

tl::optional<position> grid::goal() const { return find(position_kind::goal); }

bool grid::has_start() const { return start().has_value(); }

tl::optional<position> grid::start() const
{
    return find(position_kind::start);
}

std::ostream& operator<<(std::ostream& os, const grid& grid)
{
    grid.visualize(os);
    return os;
}

void grid::visualize(std::ostream& os)
    const // TODO: have something to 'visualize' a single position_kind
{
    // TODO: Implement this.
}

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

tl::optional<position> grid::top_neighbor(position pos) const
{
    // TODO: Implement this
}

tl::optional<position> grid::bottom_neighbor(position pos) const
{
    // TODO: Implement this
}

tl::optional<position> grid::left_neighbor(position pos) const
{
    // TODO: Implement this
}

tl::optional<position> grid::right_neighbor(position pos) const
{
    // TODO: Implement this
}

std::vector<position> grid::neighbors(position pos) const
{
    // TODO: Implement this
}
} // namespace isp1