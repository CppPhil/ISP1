/*!
 * \file identifier_with_cost.hpp
 * \brief Exports the identifier_with_cost class template.
 **/
#pragma once
#include <cost.hpp> // cost

/*!
 * \brief A node identifier along with its associated g value.
 * \tparam The type of object that identifies a node.
 **/
template<typename NodeIdentifier>
class identifier_with_cost {
public:
    /*!
     * \brief Creates a new identifier_with_cost object.
     * \param node_identifier The node identifier to use.
     * \param g The g valuet to use.
     **/
    identifier_with_cost(NodeIdentifier node_identifier, cost g)
        : m_node_identifier(node_identifier), m_g(g)
    {
    }

    /*!
     * \brief Read accessor for the node identifier.
     * \return The node identifier.
     **/
    NodeIdentifier node_identifier() const { return m_node_identifier; }

    /*!
     * \brief Read accessor for the g value.
     * \return The g value.
     **/
    cost g() const { return m_g; }

private:
    NodeIdentifier m_node_identifier; /*!< The node identifier */
    cost           m_g;               /*!< The g value */
};
