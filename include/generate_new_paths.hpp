/*!
 * \file generate_new_paths.hpp
 * \brief Exports a function template to generate new paths.
 **/
#pragma once
#include <namespaces.hpp>
#include <path.hpp> // path
#include <vector>   // vector

/*!
 * \brief Generates new paths.
 * \param old_path The old path to use.
 * \param children The children of the last node of old_path.
 * \tparam NodeIdentifier The type of the object that is used to identify a
 *                        node.
 * \return The newly generated paths.
 *
 * Generates new paths by appending old_path with each of the children
 * individually.
 **/
template<typename NodeIdentifier>
vector<path<NodeIdentifier>> generate_new_paths(
    const path<NodeIdentifier>&                         old_path,
    const vector<identifier_with_cost<NodeIdentifier>>& children)
{
    vector<path<NodeIdentifier>> result;

    // Iterate over the children
    for (const identifier_with_cost<NodeIdentifier>& child : children) {
        // Create a copy of the old_path
        path<NodeIdentifier> copy = old_path;

        // Modify that local copy by appending the current child to it.
        copy.append(child);

        // Add that newly created path to the result vector.
        result.push_back(copy);
    }

    return result;
}
