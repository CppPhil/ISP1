#pragma once
#include <path.hpp> // Path
#include <vector>   // std::vector

template<typename NodeIdentifier>
std::vector<Path<NodeIdentifier>> generateNewPaths(
    const Path<NodeIdentifier>&                            oldPath,
    const std::vector<IdentifierWithCost<NodeIdentifier>>& children)
{
    std::vector<Path<NodeIdentifier>> result{};

    for (const IdentifierWithCost<NodeIdentifier>& child : children) {
        Path<NodeIdentifier> copy{oldPath};
        copy.append(child);
        result.push_back(std::move(copy));
    }

    return result;
}
