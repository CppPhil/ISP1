/*!
 * \file contains.hpp
 * \brief Exports a function template to check whether a container contains an
 *        object.
 **/
#pragma once
#include <namespaces.hpp>
#include <pl/algo/ranged_algorithms.hpp> // find

/*!
 * \brief Queries a container as to whether it contains a given value.
 * \param container The container to query.
 * \param value The value to find.
 * \tparam Container The type of the container.
 * \tparam Type The type of the value to find.
 * \return true if container contains value; false otherwise.
 **/
template<typename Container, typename Type>
bool contains(const Container& container, const Type& value)
{
    // the find algorithm will return the container's end iterator if the object
    // wasn't found.
    return find(container, value) != container.end();
}
