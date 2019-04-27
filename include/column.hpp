/*!
 * \file column.hpp
 * \brief Exports the column type.
 **/
#pragma once
#include <cstddef>         // std::size_t
#include <total_order.hpp> // TOTAL_ORDER

// See https://en.cppreference.com/w/cpp/language/explicit for reference of the
// explicit keyword

namespace isp1 {
/*!
 * \brief Type to represent a column in a grid.
 **/
class column {
public:
    typedef std::size_t value_type;

    /*!
     * \brief Creates a column object.
     * \param value The column value to use.
     **/
    explicit column(value_type value);

    /*!
     * \brief Read accessor for the column value.
     * \return The column value.
     **/
    value_type value() const;

private:
    value_type m_value; /*!< The underlying column value */
};

/*!
 * \brief Less than comparison for column object.
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 * \return true if lhs is deemed less than rhs; otherwise false.
 **/
bool operator<(column lhs, column rhs);

TOTAL_ORDER(column)
} // namespace isp1