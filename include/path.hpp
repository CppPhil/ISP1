#pragma once
#include <cost.hpp>                 // Cost
#include <cstddef>                  // size_t
#include <identifier_with_cost.hpp> // IdentifierWithCost
#include <initializer_list>         // initializer_list
#include <namespaces.hpp>
#include <stdexcept> // out_of_range
#include <utility>   // move
#include <vector>    // vector

template<typename NodeIdentifier>
class Path {
public:
    using this_type        = Path;
    using container_type   = vector<IdentifierWithCost<NodeIdentifier>>;
    using iterator         = typename container_type::iterator;
    using const_iterator   = typename container_type::const_iterator;
    using reverse_iterator = typename container_type::reverse_iterator;
    using const_reverse_iterator =
        typename container_type::const_reverse_iterator;

    Path() = default;

    Path(initializer_list<IdentifierWithCost<NodeIdentifier>> initL)
        : m_vector(initL.begin(), initL.end())
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
        m_vector.emplace_back(move(nodeIdentifier), g);
    }

    void append(IdentifierWithCost<NodeIdentifier> identifierWithCost)
    {
        m_vector.push_back(move(identifierWithCost));
    }

    size_t size() const noexcept { return m_vector.size(); }

    bool isEmpty() const noexcept { return m_vector.empty(); }

    IdentifierWithCost<NodeIdentifier>& front()
    {
        if (isEmpty()) {
            throw out_of_range{"front may not be called on an empty path."};
        }

        return m_vector.front();
    }

    const IdentifierWithCost<NodeIdentifier>& front() const
    {
        return const_cast<this_type*>(this)->front();
    }

    IdentifierWithCost<NodeIdentifier>& back()
    {
        if (isEmpty()) {
            throw out_of_range{"back may not be called on an empty path."};
        }

        return m_vector.back();
    }

    const IdentifierWithCost<NodeIdentifier>& back() const
    {
        return const_cast<this_type*>(this)->back();
    }

    Cost g() const noexcept
    {
        Cost cost{};

        for (const IdentifierWithCost<NodeIdentifier>& identifierWithCost :
             m_vector) {
            cost += identifierWithCost.g();
        }

        return cost;
    }

private:
    vector<IdentifierWithCost<NodeIdentifier>> m_vector;
};
