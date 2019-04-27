/*!
 * \file identifier_with_cost.hpp
 * \brief Exports the identifier_with_cost class template.
 **/
#pragma once
#include <cost.hpp> // isp1::cost
#include <ostream>  // std::ostream
#include <sstream>  // std::ostringstream

namespace isp1{
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

/*!
 * \brief Writes an identifier_with_cost to an ostream.
 * \param os The ostream to write to.
 * \param id_w_cost The identifier_with_cost to print.
 * \tparam NodeIdentifier type used to identify a node.
 * \return A reference to os.
 **/
template<typename NodeIdentifier>
std::ostream& operator<<(std::ostream& os, identifier_with_cost<NodeIdentifier> id_w_cost)
{
    os << "{\"node_identifier\": \"" << id_w_cost.node_identifier() << "\", "
       << "\"g\": " << id_w_cost.g() << '}';

    return os;
}
} // namespace isp1
