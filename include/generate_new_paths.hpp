#pragma once
#include <namespaces.hpp>
#include <path.hpp> // path
#include <vector>   // vector

template<typename NodeIdentifier>
vector<path<NodeIdentifier>> generate_new_paths(
    const path<NodeIdentifier>&                         old_path,
    const vector<identifier_with_cost<NodeIdentifier>>& children)
{
    vector<path<NodeIdentifier>> result;

    for (const identifier_with_cost<NodeIdentifier>& child : children) {
        path<NodeIdentifier> copy = old_path;
        copy.append(child);
        result.push_back(copy);
    }

    return result;
}
