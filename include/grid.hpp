/*!
 * \file grid.hpp
 * \brief Exports the grid type.
 **/
#pragma once
#include <column.hpp>        // isp1::column
#include <cost.hpp>          // isp1::cost
#include <graph_t.hpp>       // isp1::graph_t
#include <ostream>           // std::ostream
#include <path.hpp>          // isp1::path
#include <position.hpp>      // isp1::position
#include <position_kind.hpp> // isp1::position_kind
#include <row.hpp>           // isp1::row
#include <string>            // std::string
#include <tl/optional.hpp>   // tl::optional
#include <vector>            // std::vector

namespace isp1 {
/*!
 * \brief Type to represent a grid for the grid world.
 **/
class grid {
public:
    typedef grid this_type;

    /*!
     * \brief Creates a grid of the specified size.
     * \param column_count The amount of columns that the
     *                     grid shall have.
     * \param row_count The amount of rows that the grid
     *                  shall have.
     * \throws out_of_range if a value of 0 is given.
     **/
    grid(column column_count, row row_count);

    /*!
     * \brief Queries for the amount of columns.
     * \return The amount of columns.
     **/
    column column_count() const;

    /*!
     * \brief Queries for the amount of rows.
     * \return The amount of rows.
     **/
    row row_count() const;

    /*!
     * \brief Fetches a reference to the position_kind at the provided position.
     * \param position The position to use.
     * \return A reference to the position_kind at position.
     * \throws out_of_range if position is out of bounds.
     **/
    position_kind& at(position position);

    /*!
     * \brief Fetches a const reference to the position_kind at the provided
     *        position.
     * \param position The position to use.
     * \return A const reference
     *         to the position_kind at position.
     * \throws out_of_range if position is out
     *                      of bounds.
     **/
    const position_kind& at(position position) const;

    /*!
     * \brief Creates a graph for this grid that the A* algorithm may be used
     *        on. The graph will only contain the positions as nodes that
     *        aren't walls.
     * \return The resulting graph.
     **/
    graph_t<position, cost, UNDIRECTED> graph() const;

    /*!
     * \brief Inserts a search path into the grid.
     * \param result_path The search path returned by A*.
     *
     * Replaces the position_kind of all the positions in the path
     * given with the on_path position kind if they were previously
     * empty.
     **/
    void insert_path(const path<position>& result_path);

    /*!
     * \brief Queries whether this grid has a goal.
     * \return true if this grid has a goal; otherwise false.
     **/
    bool has_goal() const;

    /*!
     * \brief Returns the goal of this grid.
     * \return The goal of this grid or nullopt if this grid has no goal.
     **/
    tl::optional<position> goal() const;

    /*!
     * \brief Queries whether this grid has a start.
     * \return true if this grid has a start; otherwise false.
     **/
    bool has_start() const;

    /*!
     * \brief Returns the start of this grid.
     * \return The start of this grid or nullopt if there's no start.
     **/
    tl::optional<position> start() const;

    /*!
     * \brief Turns this grid into a string.
     * \return The resulting string.
     **/
    std::string to_string() const;

    /*!
     * \brief Prints a grid to an ostream.
     * \param os The ostream to print to.
     * \return A reference to os.
     **/
    friend std::ostream& operator<<(std::ostream& os, const grid& grid);

private:
    /*!
     * \brief Fetches the column vector at the specified column.
     * \param value The column vector to fetch.
     * \return A reference to the column vector requested.
     **/
    std::vector<position_kind>& get_column(column value);

    /*!
     * \brief Fetches the column vector at the specified column.
     * \param value The column vector to fetch.
     * \return A const reference to the column vector requested.
     **/
    const std::vector<position_kind>& get_column(column value) const;

    /*!
     * \brief Finds a position with the specified position kind.
     * \param kind The position kind to find.
     * \return The position with the position kind given or nullopt
     *         if no such position exists.
     **/
    tl::optional<position> find(position_kind kind) const;

    /*!
     * \brief Returns the top neighbor of pos if there's one.
     * \param pos The position to get the top neighbor of.
     * \return The top neighbor of pos or nullopt if there's no
     *         top neighbor.
     **/
    tl::optional<position> top_neighbor(position pos) const;

    /*!
     * \brief Returns the bottom neighbor of pos if there's one.
     * \param pos The position to get the bottom neighbor of.
     * \return The bottom neighbor of pos or nullopt if there's
     *         no bottom neighbor.
     **/
    tl::optional<position> bottom_neighbor(position pos) const;

    /*!
     * \brief Returs the left neighbor of pos if there's one.
     * \param pos The position to get the left neighbor of.
     * \return The left neighbor of pos or nullopt if there's
     *         no left neighbor.
     **/
    tl::optional<position> left_neighbor(position pos) const;

    /*!
     * \brief Returns the right neigbor of pos if there's one.
     * \param pos The position to get the right neighbor of.
     * \return The rigth neighbor of pos or nullopt if there's
     *         no right neighbor.
     **/
    tl::optional<position> right_neighbor(position pos) const;

    /*!
     * \brief Returns all the neighbors of a given position.
     * \param pos The position to get the neighbors of.
     * \return The neighbors of pos.
     **/
    std::vector<position> neighbors(position pos) const;

    std::vector<std::vector<position_kind>> m_data; /*!< The underlying data */
};
} // namespace isp1
