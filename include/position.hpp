/*!
 * \file position.hpp
 * \brief Exports the position type.
 **/
#pragma once
#include <column.hpp> // isp1::column
#include <row.hpp>    // isp1::row

// TODO: Make shit be totally ordered

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
 * \brief Compares two positions for equality.
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 * \return true if the two positions are equal; otherwise false.
 **/
bool operator==(position lhs, position rhs);

/*!
 * \brief Compares two positions for inequality.
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 * \return true if the two positions are not equal; otherwise false.
 **/
bool operator!=(position lhs, position rhs);
} // namespace isp1