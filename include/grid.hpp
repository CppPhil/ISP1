#pragma once
#include <column.hpp>        // isp1::column
#include <cost.hpp>          // isp1::cost
#include <graph_t.hpp>       // isp1::graph_t
#include <ostream>           // std::ostream
#include <path.hpp>          // isp1::path
#include <position.hpp>      // isp1::position
#include <position_kind.hpp> // isp1::position_kind
#include <row.hpp>           // isp1::row
#include <tl/optional.hpp>   // tl::optional
#include <vector>            // std::vector

// TODO: DOCUMENTATION

namespace isp1 {
// TODO: TEST THIS STUFF
class grid {
public:
    typedef grid this_type;

    grid(column column_count, row row_count);

    column column_count() const;

    row row_count() const;

    position_kind& at(position position);

    const position_kind& at(position position) const;

    graph_t<position, cost, UNDIRECTED> as_graph() const;

    void insert_path(const path<position>& result_path);

    bool has_goal() const;

    tl::optional<position> goal() const;

    bool has_start() const;

    tl::optional<position> start() const;

    friend std::ostream& operator<<(std::ostream& os, const grid& grid);

private:
    void visualize(std::ostream& os) const;

    std::vector<position_kind>& get_column(column value);

    const std::vector<position_kind>& get_column(column value) const;

    tl::optional<position> find(position_kind kind) const;

    tl::optional<position> top_neighbor(position pos) const;

    tl::optional<position> bottom_neighbor(position pos) const;

    tl::optional<position> left_neighbor(position pos) const;

    tl::optional<position> right_neighbor(position pos) const;

    std::vector<position> neighbors(position pos) const;

    std::vector<std::vector<position_kind>> m_data;
};
} // namespace isp1
