/*!
 * \file total_order.hpp
 * \brief Exports the TOTAL_ORDER macro.
 **/
#pragma once
#include <ciso646> // not, and

/*!
 * \def TOTAL_ORDER
 * \brief Defines a total ordering for the type given.
 * \warning There must be a correct operator< already defined for type.
 **/
#define TOTAL_ORDER(type)                                    \
    inline bool operator==(const type& lhs, const type& rhs) \
    {                                                        \
        return (not(lhs < rhs)) and (not(rhs < lhs));        \
    }                                                        \
                                                             \
    inline bool operator!=(const type& lhs, const type& rhs) \
    {                                                        \
        return not(lhs == rhs);                              \
    }                                                        \
                                                             \
    inline bool operator>(const type& lhs, const type& rhs)  \
    {                                                        \
        return rhs < lhs;                                    \
    }                                                        \
                                                             \
    inline bool operator<=(const type& lhs, const type& rhs) \
    {                                                        \
        return not(lhs > rhs);                               \
    }                                                        \
                                                             \
    inline bool operator>=(const type& lhs, const type& rhs) \
    {                                                        \
        return not(lhs < rhs);                               \
    }
