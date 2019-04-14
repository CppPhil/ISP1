#ifndef INCG_ISP1_IDENTIFIER_WITH_COST_HPP
#define INCG_ISP1_IDENTIFIER_WITH_COST_HPP
#include <cost.hpp> // isp1::Cost
#include <utility>  // std::move

namespace isp1 {
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
} // namespace isp1
#endif // INCG_ISP1_IDENTIFIER_WITH_COST_HPP