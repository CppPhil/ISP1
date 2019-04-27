/*!
 * \file column.hpp
 * \brief Exports the column type.
 **/
#pragma once
#include <cstddef> // size_t
#include <namespaces.hpp>

// See https://en.cppreference.com/w/cpp/language/explicit for reference of the
// explicit keyword

/*!
 * \brief Type to represent a column in a grid.
 **/
class column {
public:
    typedef size_t value_type;

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
 * \brief Compares two columns for equality.
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 * \return true if the two columns are equal; otherwise false.
 **/
bool operator==(column lhs, column rhs);

/*!
 * \brief Compares two for inequality.
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 * \return true if the two columns are not equal; otherwise false.
 **/
bool operator!=(column lhs, column rhs);
