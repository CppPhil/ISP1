/*!
 * \file position_kind.hpp
 * \brief Exports the position_kind enum.
 **/
#pragma once

// Regarding use of enum class see:
// https://stackoverflow.com/questions/18335861/why-is-enum-class-preferred-over-plain-enum

/*!
 * \brief Enum for the kind of a position in a grid.
 * \note The underlying type used is int.
 **/
enum class position_kind : int {
    start = 1,  /*!< The position in the grid is a start position */
    goal  = 2,  /*!< The position in the grid is a goal position */
    empty = 3,  /*!< The position in the grid is an empty position */
    wall  = 4,  /*!< The position in the grid is a wall,
                 *   hence it can't be traversed
                 **/
    on_path = 5 /*!< The position in the grid is part of the shortest path from
                 *   start to goal found by A*
                 **/
};
