/*!
 * \file position.hpp
 * \brief Exports the position type.
 **/
#pragma once
#include <column.hpp>      // isp1::column
#include <row.hpp>         // isp1::row
#include <total_order.hpp> // TOTAL_ORDER

// Here the class keyword is used as a disambiguator so that (member) functions
// may be declared using the same identifier.

namespace isp1 {
/*!
 * \brief Type used for the positions in a grid.
 **/
class position {
public:
    /*!
     * \brief Creates a position object.
     * \param column The column to use.
     * \param row The row to use.
     **/
    position(class column column, class row row);

    /*!
     * \brief Read accessor for the column.
     * \return The column.
     **/
    class column column() const;

    /*!
     * \brief Read accessor for the row.
     * \return The row.
     **/
    class row row() const;

private:
    class column m_column; /*!< The underlying column */
    class row    m_row;    /*!< The underlying row */
};

/*!
 * \brief Prints a position.
 * \param os The ostream to print to.
 * \param pos The position to print.
 * \return A reference to os.
 **/
std::ostream& operator<<(std::ostream& os, position pos);

/*!
 * \brief Less than comparison of positions.
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 * \return true if lhs is deemed less than rhs; false otherwise.
 * \note The columns are compared first and if they're the same
 *       then the rows are compared.
 **/
bool operator<(position lhs, position rhs);

TOTAL_ORDER(position)
} // namespace isp1