#pragma once
#include <cost.hpp> // Cost
#include <utility>  // std::move

template<typename NodeIdentifier>
class IdentifierWithCost {
public:
    IdentifierWithCost(NodeIdentifier nodeIdentifier, Cost g)
        : m_nodeIdentifier{std::move(nodeIdentifier)}, m_g{g}
    {
    }

    NodeIdentifier nodeIdentifier() const { return m_nodeIdentifier; }

    Cost g() const noexcept { return m_g; }

private:
    NodeIdentifier m_nodeIdentifier;
    Cost           m_g;
};
