#ifndef INCG_ISP1_PATH_HPP
#define INCG_ISP1_PATH_HPP
#include <cost.hpp>         // isp1::Cost
#include <cstddef>          // std::size_t
#include <initializer_list> // std::initializer_list
#include <iterator>         // std::begin, std::end
#include <stdexcept>        // std::out_of_range
#include <utility>          // std::move
#include <vector>           // std::vector

namespace isp1 {
template<typename NodeIdentifier>
struct IdentifierWithCost {
    IdentifierWithCost(NodeIdentifier p_nodeIdentifier, Cost p_g)
        : nodeIdentifier{std::move(p_nodeIdentifier)}, g{p_g}
    {
    }

    NodeIdentifier nodeIdentifier;
    Cost           g;
};

template<typename NodeIdentifier>
class Path {
public:
    using this_type        = Path;
    using container_type   = std::vector<IdentifierWithCost<NodeIdentifier>>;
    using iterator         = typename container_type::iterator;
    using const_iterator   = typename container_type::const_iterator;
    using reverse_iterator = typename container_type::reverse_iterator;
    using const_reverse_iterator =
        typename container_type::const_reverse_iterator;

    Path() = default;

    Path(std::initializer_list<IdentifierWithCost<NodeIdentifier>> initL)
        : m_vector(std::begin(initL), std::end(initL))
    {
    }

    iterator begin() noexcept { return m_vector.begin(); }

    const_iterator begin() const noexcept { return m_vector.begin(); }

    const_iterator cbegin() const noexcept { return m_vector.cbegin(); }

    iterator end() noexcept { return m_vector.end(); }

    const_iterator end() const noexcept { return m_vector.end(); }

    const_iterator cend() const noexcept { return m_vector.cend(); }

    reverse_iterator rbegin() noexcept { return m_vector.rbegin(); }

    const_reverse_iterator rbegin() const noexcept { return m_vector.rbegin(); }

    const_reverse_iterator crbegin() const noexcept
    {
        return m_vector.crbegin();
    }

    reverse_iterator rend() noexcept { return m_vector.rend(); }

    const_reverse_iterator rend() const noexcept { return m_vector.rend(); }

    const_reverse_iterator crend() const noexcept { return m_vector.crend(); }

    void append(NodeIdentifier nodeIdentifier, Cost g)
    {
        m_vector.emplace_back(std::move(nodeIdentifier), g);
    }

    void append(IdentifierWithCost<NodeIdentifier> identifierWithCost)
    {
        m_vector.push_back(std::move(identifierWithCost));
    }

    std::size_t size() const noexcept { return m_vector.size(); }

    bool isEmpty() const noexcept { return m_vector.empty(); }

    IdentifierWithCost<NodeIdentifier>& front() noexcept
    {
        if (isEmpty()) {
            throw std::out_of_range{
                "front may not be called on an empty path."};
        }

        return m_vector.front();
    }

    const IdentifierWithCost<NodeIdentifier>& front() const noexcept
    {
        return const_cast<this_type*>(this)->front();
    }

    IdentifierWithCost<NodeIdentifier>& back() noexcept
    {
        if (isEmpty()) {
            throw std::out_of_range{"back may not be called on an empty path."};
        }

        return m_vector.back();
    }

    const IdentifierWithCost<NodeIdentifier>& back() const noexcept
    {
        return const_cast<this_type*>(this)->back();
    }

    Cost g() const noexcept
    {
        Cost cost{};

        for (const IdentifierWithCost<NodeIdentifier>& identifierWithCost :
             m_vector) {
            cost += identifierWithCost.g;
        }

        return cost;
    }

private:
    std::vector<IdentifierWithCost<NodeIdentifier>> m_vector;
};
} // namespace isp1
#endif // INCG_ISP1_PATH_HPP
