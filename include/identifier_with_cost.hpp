#pragma once
#include <cost.hpp> // Cost

template<typename NodeIdentifier>
class IdentifierWithCost {
public:
    IdentifierWithCost(NodeIdentifier nodeIdentifier, Cost g)
        : m_nodeIdentifier{nodeIdentifier}, m_g{g}
    {
    }

    NodeIdentifier nodeIdentifier() const { return m_nodeIdentifier; }

    Cost g() const { return m_g; }

private:
    NodeIdentifier m_nodeIdentifier;
    Cost           m_g;
};
