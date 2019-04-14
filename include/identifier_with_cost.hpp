#pragma once
#include <cost.hpp> // cost

template<typename NodeIdentifier>
class identifier_with_cost {
public:
    identifier_with_cost(NodeIdentifier node_identifier, cost g)
        : m_node_identifier(node_identifier), m_g(g)
    {
    }

    NodeIdentifier node_identifier() const { return m_node_identifier; }

    cost g() const { return m_g; }

private:
    NodeIdentifier m_node_identifier;
    cost           m_g;
};
