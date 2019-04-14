#pragma once
#include <namespaces.hpp>
#include <path.hpp> // Path
#include <vector>   // vector

template<typename NodeIdentifier>
vector<Path<NodeIdentifier>> generateNewPaths(
    const Path<NodeIdentifier>&                       oldPath,
    const vector<IdentifierWithCost<NodeIdentifier>>& children)
{
    vector<Path<NodeIdentifier>> result{};

    for (const IdentifierWithCost<NodeIdentifier>& child : children) {
        Path<NodeIdentifier> copy{oldPath};
        copy.append(child);
        result.push_back(copy);
    }

    return result;
}
