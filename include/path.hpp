#pragma once
#include <cost.hpp>                 // cost
#include <cstddef>                  // size_t
#include <identifier_with_cost.hpp> // identifier_with_cost
#include <initializer_list>         // initializer_list
#include <namespaces.hpp>
#include <stdexcept> // out_of_range
#include <vector>    // vector

template<typename NodeIdentifier>
class path {
public:
    typedef path                                         this_type;
    typedef vector<identifier_with_cost<NodeIdentifier>> container_type;
    typedef typename container_type::iterator            iterator;
    typedef typename container_type::const_iterator      const_iterator;
    typedef typename container_type::reverse_iterator    reverse_iterator;
    typedef
        typename container_type::const_reverse_iterator const_reverse_iterator;

    path() = default;

    path(initializer_list<identifier_with_cost<NodeIdentifier>> init_list)
        : m_vector(init_list.begin(), init_list.end())
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

    void append(NodeIdentifier identifier, cost g)
    {
        m_vector.emplace_back(identifier, g);
    }

    void append(identifier_with_cost<NodeIdentifier> identifier)
    {
        m_vector.push_back(identifier);
    }

    size_t size() const { return m_vector.size(); }

    bool is_empty() const { return m_vector.empty(); }

    identifier_with_cost<NodeIdentifier>& front()
    {
        if (is_empty()) {
            throw out_of_range("front may not be called on an empty path.");
        }

        return m_vector.front();
    }

    const identifier_with_cost<NodeIdentifier>& front() const
    {
        return const_cast<this_type*>(this)->front();
    }

    identifier_with_cost<NodeIdentifier>& back()
    {
        if (is_empty()) {
            throw out_of_range("back may not be called on an empty path.");
        }

        return m_vector.back();
    }

    const identifier_with_cost<NodeIdentifier>& back() const
    {
        return const_cast<this_type*>(this)->back();
    }

    cost g() const
    {
        cost the_cost = 0;

        for (const identifier_with_cost<NodeIdentifier>& identifier :
             m_vector) {
            the_cost += identifier.g();
        }

        return the_cost;
    }

private:
    vector<identifier_with_cost<NodeIdentifier>> m_vector;
};
