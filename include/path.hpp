#pragma once
#include <cost.hpp>                 // Cost
#include <cstddef>                  // size_t
#include <identifier_with_cost.hpp> // IdentifierWithCost
#include <initializer_list>         // initializer_list
#include <namespaces.hpp>
#include <stdexcept> // out_of_range
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

    iterator begin() { return m_vector.begin(); }

    const_iterator begin() const { return m_vector.begin(); }

    const_iterator cbegin() const { return m_vector.cbegin(); }

    iterator end() { return m_vector.end(); }

    const_iterator end() const { return m_vector.end(); }

    const_iterator cend() const { return m_vector.cend(); }

    reverse_iterator rbegin() { return m_vector.rbegin(); }

    const_reverse_iterator rbegin() const { return m_vector.rbegin(); }

    const_reverse_iterator crbegin() const { return m_vector.crbegin(); }

    reverse_iterator rend() { return m_vector.rend(); }

    const_reverse_iterator rend() const { return m_vector.rend(); }

    const_reverse_iterator crend() const { return m_vector.crend(); }

    void append(NodeIdentifier nodeIdentifier, Cost g)
    {
        m_vector.emplace_back(nodeIdentifier, g);
    }

    void append(IdentifierWithCost<NodeIdentifier> identifierWithCost)
    {
        m_vector.push_back(identifierWithCost);
    }

    size_t size() const { return m_vector.size(); }

    bool isEmpty() const { return m_vector.empty(); }

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

    Cost g() const
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
