/*!
 * \file row.hpp
 * \brief Exports the row type.
 **/
#pragma once
#include <cstddef> // size_t
#include <namespaces.hpp>

/*!
 * \brief Type used for the rows in a grid.
 **/
class row {
public:
    typedef size_t value_type;

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
 * \brief Compares two rows for equality.
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 * \return true if the two rows are equal; otherwise false.
 **/
bool operator==(row lhs, row rhs);

/*!
 * \brief Compares two rows for inequality.
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 * \return true if the two rows are not equal; otherwise false.
 **/
bool operator!=(row lhs, row rhs);
