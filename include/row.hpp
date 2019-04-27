/*!
 * \file row.hpp
 * \brief Exports the row type.
 **/
#pragma once
#include <cstddef>         // std::size_t
#include <total_order.hpp> // TOTAL_ORDER

namespace isp1 {
/*!
 * \brief Type used for the rows in a grid.
 **/
class row {
public:
    typedef std::size_t value_type;

    /*!
     * \brief Creates a new row object.
     * \param value The row value to use.
     **/
    explicit row(value_type value);

    /*!
     * \brief Read accessor for the row value.
     * \return The row value.
     **/
    value_type value() const;

private:
    value_type m_value; /*!< The underlying row value */
};

/*!
 * \brief Less than comparison of row object.
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 * \return true if lhs is deemed less than rhs; otherwise false.
 **/
bool operator<(row lhs, row rhs);

TOTAL_ORDER(row)
} // namespace isp1